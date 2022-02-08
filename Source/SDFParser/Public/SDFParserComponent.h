#pragma once

#include "CoreMinimal.h"
#include "SDFParserStructs.h"
#include "Components/ActorComponent.h"
#include "SDFParserComponent.generated.h"

/** 
 * SDF Parser actor component. Attach to any actor (including GameMode). No initialisation required.
 * Used to open a MOL file (.SDF format), parse, validate and transfer into a custom data structure.
 */
UCLASS(BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class USDFParserComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	// Get all files in the directory provided.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	TArray<FString> GetAllFilesInDirectory(const FString Dir, const bool bFullPath, const FString ExtensionFilter) const;

	// Load the file specified into an array of strings for parsing. Returns false upon failure.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	bool LoadFile(const FString FullPath, TArray<FString> &Data);

	// Parse an SDF file following the standard format and definition.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	ESDFParseResult Parse(const TArray<FString> Data, TArray<FMolecule> &Molecule);

	// Use right and left chops to return a substring.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	FString GetSubString(const FString String, int32 StartIndex, int32 Length);

	// Parse a string into an atom structure. Return true if successful.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	bool ParseAtomString(FString String, FAtom &Atom);

	// Parse a string into a bond structure. Return true if successful.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	bool ParseBondString(const FString String, FBond& Bond);

	// Match an atomic element symbol string to its corresponding enum.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	bool GetAtomElement(FString Symbol, EAtomicElement &AtomicElement) const;

	// Return the string for a given atom enum.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	bool GetAtomElementString(EAtomicElement AtomicElement, FString& ElementName) const;

	// Parse an atom charge or isotope property string in order to retrieve up to eight entries.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	bool ParseProperties(const FString String, TArray<FIntPoint>& Properties);

	// Map the charge value to the atom charge enum.
	UFUNCTION(BlueprintCallable, Category="SDF Parser")
	EAtomCharge GetAtomCharge(int32 ChargeValue) const ;
};
