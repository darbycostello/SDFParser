#include "SDFParserComponent.h"
#include "Misc/LocalTimestampDirectoryVisitor.h"

/**
 * Get all files in the directory provided.
 * @param Dir The full path of the directory we want to iterate over.
 * @param bFullPath Whether to return full paths or just file names.
 * @param ExtensionFilter Will filter only filenames with the given extension.
 */
TArray<FString> USDFParserComponent::GetAllFilesInDirectory(
	const FString Dir,
	const bool bFullPath,
	const FString ExtensionFilter) const {

	// This is a recursive search so do not accept an empty or root folder.
	if (Dir.IsEmpty() || Dir == FPaths::RootDir()) return TArray<FString>();
	
	const TArray<FString> IgnoreDirs;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FLocalTimestampDirectoryVisitor Visitor(PlatformFile, IgnoreDirs, IgnoreDirs, false);
	PlatformFile.IterateDirectory(*Dir, Visitor);
	TArray<FString> Files;

	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt) {
		const FString Path = TimestampIt.Key();
		const FString FileName = FPaths::GetCleanFilename(Path);

		// Check if file extension filter matches.
		if (!ExtensionFilter.IsEmpty()) {
			if (!FPaths::GetExtension(FileName, false).Equals(ExtensionFilter, ESearchCase::IgnoreCase))
				continue;
		}

		// Add full path to results.
		Files.Add(bFullPath ? Path : FileName);
	}
	return Files;
}

/**
 * Load the file specified into an array of strings for parsing. Returns false upon failure.
 * @param FullPath The file to load.
 * @param Data The string array to parse the file into.
 */
bool USDFParserComponent::LoadFile(const FString FullPath, TArray<FString>& Data) {
	return FFileHelper::LoadFileToStringArray(Data, *FullPath);
}

/**
 * Parse an SDF file following the standard format and definition.
 * Performs concurrent validation and returns early on failure.
 * (See: http://www.nonlinear.com/progenesis/sdf-studio/v0.9/faq/sdf-file-format-guidance.aspx).
 * @param Data The string array to parse the file into.
 * @param Molecules The complete list of Molecule structures to return.
 */
ESDFParseResult USDFParserComponent::Parse(const TArray<FString> Data, TArray<FMolecule>& Molecules) {

	// Idiot check.
	if (Data.Num() < 1) return ESDFParseResult::Empty;

	// Minimum length (Name + Generator + Comment + Counts + Atom + Molecule End + Terminator = 7).
	if (Data.Num() < 7) {
		UE_LOG(LogTemp, Warning, TEXT("Array length less than 7"));
		return ESDFParseResult::Invalid;
	}

	Molecules = TArray<FMolecule>();
	int32 It = 0;

	while (true) {
		if (Data.Num() <= It) {
			UE_LOG(LogTemp, Warning, TEXT("Molecules: End of array at index %d"), It);
			break;
		}
		
		// Start with a new molecule model.
		FMolecule Molecule;
		
		// Parse the name if one exists.
		if (!Data[It].IsEmpty()) {
			Molecule.Name = FName(*Data[It]);
			UE_LOG(LogTemp, Display, TEXT("Molecule Name: %s"), *Molecule.Name.ToString());
		}
		
		// Parse the originator if one exists.
		It++;
		if (!Data[It].IsEmpty()) {
			Molecule.Originator = Data[It];
			UE_LOG(LogTemp, Display, TEXT("Originator: %s"), *Molecule.Originator);
		}
		
		// Parse the comment if one exists.
		It++;
		if (!Data[It].IsEmpty()) {
			Molecule.Comment = Data[It];
			UE_LOG(LogTemp, Display, TEXT("Comment: %s"), *Molecule.Comment);
		}

		// Parse the counts. Must be 12 characters in length.
		It++;
		if (Data[It].Len() < 12) {
			UE_LOG(LogTemp, Warning, TEXT("Counts length less than 12"));
			return ESDFParseResult::Invalid;
		}

		// Parse the atom count - this will be used to validate the atoms list.
		const int32 AtomCount = FCString::Atoi(*GetSubString(Data[It], 0, 3));
		UE_LOG(LogTemp, Log, TEXT("Atom count: %d"), AtomCount);

		// Parse the bond count - this will be used to validate the bonds list.
		const int32 BondCount = FCString::Atoi(*GetSubString(Data[It], 3, 3));
		UE_LOG(LogTemp, Log, TEXT("Bond count: %d"), BondCount);

		// Parse the chirality.
		const int32 Chiral = FCString::Atoi(*GetSubString(Data[It], 12, 3));
		UE_LOG(LogTemp, Log, TEXT("Chiral is: %s"), Chiral == 1 ? "true" : "false");
		Molecule.bChiral = Chiral == 1;

		// Parse the version
		const FString Version = GetSubString(Data[It], 33, 6);
		UE_LOG(LogTemp, Log, TEXT("File version: %s"), *Version);
		Molecule.Version = Version;

		// Parse each atom until a validation failure or other exception occurs.
		It++;
		while (true) {
			// While true is an anti-pattern, except when used with a definite terminating condition, as below.
			if (Data.Num() <= It) {
				UE_LOG(LogTemp, Warning, TEXT("Atoms: Unexpected end of array at index %d"), It);
				break;
			}
			FAtom Atom;
			if (!ParseAtomString(Data[It], Atom)) {
				break;
			}
			Molecule.Atoms.Add(Atom);
			It++;
		}
		if (Molecule.Atoms.Num() != AtomCount) {
			UE_LOG(LogTemp, Warning, TEXT("Atoms mismatch. Expected %d entries. Found %d"), AtomCount, Molecule.Atoms.Num());
			return ESDFParseResult::AtomsMismatch;
		}

		// Parse each bond until a validation failure or other exception occurs.
		while (true) {
			// Again, use a definite terminating condition to break the while loop. 
			if (Data.Num() <= It) {
				UE_LOG(LogTemp, Warning, TEXT("Bonds: Unexpected end of array at index %d"), It);
				break;
			}
			FBond Bond;
			if (!ParseBondString(Data[It], Bond)) {
				break;
			}
			Molecule.Bonds.Add(Bond);
			It++;
		}
		if (Molecule.Bonds.Num() != BondCount) {
			UE_LOG(LogTemp, Warning, TEXT("Bonds mismatch. Expected %d entries. Found %d"), BondCount, Molecule.Bonds.Num());
			return ESDFParseResult::BondsMismatch;
		}

		// Finally, parse the rest of the file for additional properties or a terminator.
		while (true) { 
			if (Data.Num() <= It) {
				UE_LOG(LogTemp, Warning, TEXT("Properties: Unexpected end of array at index %d"), It);
				break;
			}

			// Skip any junk data or empty lines.
			if (Data[It].Len() < 3) {
				It++;
				continue;
			}
			
			if (Data[It].Len() < 6) {
				// This should be the terminator.
				FString Terminator = GetSubString(Data[It], 0, 4);
				if (Terminator.Compare("$$$$") != 0) {
					UE_LOG(LogTemp, Warning, TEXT("Unexpected terminator found: %s"), *Terminator);
					// It may not be fully valid, but we have what we need.
					Molecules.Add(Molecule);
					return ESDFParseResult::ValidWithErrors;
				}
				UE_LOG(LogTemp, Display, TEXT("Terminator found: %s. Parse completed."), *Terminator);
				Molecules.Add(Molecule);
				break;
			}

			// Parse the first six characters to determine property type.
			FString PropertyString = GetSubString(Data[It], 0, 6);
			
			if (PropertyString.Compare("M  CHG") == 0) {
				TArray<FIntPoint> Charges;
				if (!ParseProperties(PropertyString, Charges)) {
					UE_LOG(LogTemp, Warning, TEXT("Error parsing charges property. Returning early."));
					Molecules.Add(Molecule);
					return ESDFParseResult::ValidWithErrors;
				}
				for (const auto Charge : Charges) {
					// Ensure that the charge atom index exists.
					if (Charge.X >= AtomCount) {
						UE_LOG(LogTemp, Warning, TEXT("Charge atom index %d does not exist. Returning early."), Charge.X);
						Molecules.Add(Molecule);
						return ESDFParseResult::ValidWithErrors;
					}
					// Update the existing atom with the additional charge entry.
					FAtom Atom = Molecule.Atoms[Charge.X];
					Atom.Properties[EAtomProperty::Charge] = Charge.Y;
					Molecule.Atoms[Charge.X] = Atom;
				}
			} else if (PropertyString.Compare("M  ISO") == 0) {
				TArray<FIntPoint> Isotopes;
				if (!ParseProperties(PropertyString, Isotopes)) {
					UE_LOG(LogTemp, Warning, TEXT("Error parsing isotopes property. Returning early."));
					Molecules.Add(Molecule);
					return ESDFParseResult::ValidWithErrors;
				}
				for (const auto Isotope : Isotopes) {
					// Ensure that the isotope atom index exists.
					if (Isotope.X >= AtomCount) {
						UE_LOG(LogTemp, Warning, TEXT("Isotope atom index %d does not exist. Returning early."), Isotope.X);
						Molecules.Add(Molecule);
						return ESDFParseResult::ValidWithErrors;
					}
					// Update the existing atom with the additional isotope entry.
					FAtom Atom = Molecule.Atoms[Isotope.X];
					Atom.Properties[EAtomProperty::Isotope] = Isotope.Y;
					Molecule.Atoms[Isotope.X] = Atom;
				}
			} else if (PropertyString.Compare("M  END") == 0) {
				UE_LOG(LogTemp, Display, TEXT("Molecule end found."));
			} else {
				UE_LOG(LogTemp, Warning, TEXT("Unknown token: %s"), *PropertyString);
			}
			It++;
		}
		It++;
	}
	// There are also a wide variety of data fields that can come after the above.
	// These can be revisited in future iterations.

	return Molecules.Num() > 0 ? ESDFParseResult::Success : ESDFParseResult::ValidWithErrors;
}

/**
 * Use right and left chops to return a substring.
 * @param String the string to split.
 * @param StartIndex the index to begin at.
 * @param Length the length of the substring from the start index.
 */
FString USDFParserComponent::GetSubString(const FString String, const int32 StartIndex, const int32 Length) {
	const FString Result = String.RightChop(StartIndex);
	return Result.Len() >= Length ? Result.LeftChop(Result.Len() - Length) : "";
}

/**
 * Parse a string into an atom structure. Return true if successful.
 * @param String the string to parse.
 * @param Atom the atom model to store results in.
 */
bool USDFParserComponent::ParseAtomString(const FString String, FAtom &Atom) {
	if (String.IsEmpty()) return false;
	//The first three fields, 10 characters long each, describe the atom's position in the X, Y, and Z dimensions.
	float Position[3];
	for (int32 Index = 0; Index < 3; Index++) {
		Position[Index] = FCString::Atof(*GetSubString(String, Index * 10, 10));
	}
	
	// After the 30 position characters is a space, then three characters for an atomic symbol.
	const FString Symbol = GetSubString(String, 31, 3);
	const bool AtomResult = GetAtomElement(Symbol, Atom.Element);
	if (!AtomResult) {
		return false;
	}
	UE_LOG(LogTemp, Display, TEXT("Parsed atomic element: %s"), *Symbol);

	// Element was found so the atom record is valid. Set each of the properties.
	Atom.Symbol = UEnum::GetValueAsString<EAtomicElement>(Atom.Element).RightChop(16);
	UE_LOG(LogTemp, Display, TEXT("Atomic Symbol: %s"), *Atom.Symbol);
	
	Atom.Position = FVector(Position[0], Position[1], Position[2]);
	UE_LOG(LogTemp, Display, TEXT("Atom Position: %s"), *Atom.Position.ToString());
	
	// Parse the mass difference if available.
	Atom.MassDifference = FCString::Atoi(*GetSubString(String, 34, 2));
	UE_LOG(LogTemp, Display, TEXT("Atom mass difference: %d"), Atom.MassDifference);

	// Parse the charge value if available.
	const int32 ChargeValue = FCString::Atoi(*GetSubString(String, 36, 3));
	Atom.Charge = GetAtomCharge(ChargeValue);
	UE_LOG(LogTemp, Display, TEXT("Atom charge: %s"), *UEnum::GetValueAsString<EAtomCharge>(Atom.Charge));
	
	return true;
}

/**
* Parse a string into a bond structure. Return true if successful.
* @param String the string to parse.
* @param Bond the bond model to store the results in.
*/
bool USDFParserComponent::ParseBondString(const FString String, FBond &Bond) {
	if (String.IsEmpty()) return false;
	// Each bond comprises seven integer values of three characters each
	int32 BondValues[7];
	for (int32 Index = 0; Index < 7; Index++) {
		BondValues[Index] = FCString::Atoi(*GetSubString(String, Index * 3, 3));
	}

	// Return if either atom index is zero, this means the bonds list has likely ended.
	if (BondValues[0] == 0 || BondValues[1] == 0) return false;
	
	// Insert the indices into the bond model, decremented to match atoms array indexing.
	Bond.AtomIndices = FIntPoint(BondValues[0] - 1, BondValues[1] - 1);
	UE_LOG(LogTemp, Display, TEXT("Bond atom indices: %d --> %d"), Bond.AtomIndices.X, Bond.AtomIndices.Y);

	// Parse the third field into the bond type
	switch (BondValues[2]) {
		case 1:  Bond.BondType = EBondType::Single; break;
		case 2:  Bond.BondType = EBondType::Double; break;
		case 3:  Bond.BondType = EBondType::Triple; break;
		case 4:  Bond.BondType = EBondType::Aromatic; break;
		default: Bond.BondType = EBondType::Other; break;
	}

	// Parse the fourth field into the bond stereoscopy
	switch (BondValues[3]) {
		case 0:  Bond.Stereoscopy = EBondStereoscopy::None; break;
		case 1:  Bond.Stereoscopy = EBondStereoscopy::Up; break;
		case 6:  Bond.Stereoscopy = EBondStereoscopy::Down; break;
		default: Bond.Stereoscopy = EBondStereoscopy::Other; break;
	}

	// There are another three fields which we will ignore for now.
	return true;
}

/**
 * Map the charge value to the atom charge enum.
 * @param ChargeValue the integer of the charge as read from the SDF.
 */
EAtomCharge USDFParserComponent::GetAtomCharge(const int32 ChargeValue) const {
	switch (ChargeValue) {
		case 7: return EAtomCharge::Minus_3;
		case 6: return EAtomCharge::Minus_2;
		case 5: return EAtomCharge::Minus_1;
		case 4: return EAtomCharge::Doublet_Radical;
		case 3: return EAtomCharge::Plus_1;
		case 2: return EAtomCharge::Plus_2;
		case 1: return EAtomCharge::Plus_3;
		default: return EAtomCharge::Neutral;
	}
}

/**
 * Parse an atom charge or isotope property string in order to retrieve up to eight entries.
 * @param String the properties string to parse
 * @param Properties the pair of values representing the atom index then the corresponding value.
 */
bool USDFParserComponent::ParseProperties(const FString String, TArray<FIntPoint> &Properties) {
	const int32 PropertyCount = FCString::Atoi(*GetSubString(String, 6, 3));
	// The declared property count should equate to the correct string length.
	// Given by (Property (6) + Property count (3) + (8) per property entry)
	if (String.Len() < 9 + PropertyCount * 8) {
		UE_LOG(LogTemp, Warning, TEXT("Property count mismatch. Fewer than the %d declared entries found"), PropertyCount);
		return false;
	}
	// Now we can safely iterate over each property entry
	for (int32 Index = 0; Index < PropertyCount; Index++) {
		const int32 AtomIndex = FCString::Atoi(*GetSubString(String, 9 + 8 * Index, 4));

		// Value is four places after the atom index.
		const int32 PropertyValue = FCString::Atoi(*GetSubString(String, 13 + 8 * Index, 4));
		Properties.Add(FIntPoint(AtomIndex - 1, PropertyValue));
	}

	return true;
}

/**
 * Match an atomic element symbol string to its corresponding enum.
 * @param Symbol the atomic symbol as parsed from the SDF.
 * @param AtomicElement the enum of the element to store the result in.
 */
bool USDFParserComponent::GetAtomElement(const FString Symbol, EAtomicElement &AtomicElement) const {
	for (EAtomicElement Enum : TEnumRange<EAtomicElement>())
	{
		if (UEnum::GetValueAsString<EAtomicElement>(Enum).RightChop(16).Compare(Symbol.TrimEnd(), ESearchCase::IgnoreCase) == 0) {
			AtomicElement = Enum;
			return true;
		}
	}
	return false;
}

/**
* Return the string for a given atom enum.
* @param AtomicElement the atomic element.
* @param ElementName the string to store the element result in.
*/
bool USDFParserComponent::GetAtomElementString(const EAtomicElement AtomicElement, FString& ElementName) const {
	if (AtomicElements.Contains(AtomicElement)) {
		ElementName = AtomicElements[AtomicElement];
		return true;
	}
	return false;
}
