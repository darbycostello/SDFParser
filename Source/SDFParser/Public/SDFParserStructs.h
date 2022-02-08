#pragma once

#include "SDFParserStructs.generated.h"

/**
 * Atomic elements.
 * These are the only ones of which the news has come to Harvard.
 * And there may be many others but they haven't been discovered.
 */
UENUM(BlueprintType)
enum class EAtomicElement : uint8 {
	H  UMETA( DisplayName = "Hydrogen" ),
    He UMETA( DisplayName = "Helium" ),
    Li UMETA( DisplayName = "Lithium" ),
    Be UMETA( DisplayName = "Beryllium" ),
    B  UMETA( DisplayName = "Boron" ),
    C  UMETA( DisplayName = "Carbon" ),
    N  UMETA( DisplayName = "Nitrogen" ),
    O  UMETA( DisplayName = "Oxygen" ),
    F  UMETA( DisplayName = "Fluorine" ),
    Ne UMETA( DisplayName = "Neon" ),
    Na UMETA( DisplayName = "Sodium" ),
    Mg UMETA( DisplayName = "Magnesium" ),
    Al UMETA( DisplayName = "Aluminum" ),
    Si UMETA( DisplayName = "Silicon" ),
    P  UMETA( DisplayName = "Phosphorus" ),
    S  UMETA( DisplayName = "Sulfur" ),
    Cl UMETA( DisplayName = "Chlorine" ),
    Ar UMETA( DisplayName = "Argon" ),
    K  UMETA( DisplayName = "Potassium" ),
    Ca UMETA( DisplayName = "Calcium" ),
    Sc UMETA( DisplayName = "Scandium" ),
    Ti UMETA( DisplayName = "Titanium" ),
    V  UMETA( DisplayName = "Vanadium" ),
    Cr UMETA( DisplayName = "Chromium" ),
    Mn UMETA( DisplayName = "Manganese" ),
    Fe UMETA( DisplayName = "Iron" ),
    Co UMETA( DisplayName = "Cobalt" ),
    Ni UMETA( DisplayName = "Nickel" ),
    Cu UMETA( DisplayName = "Copper" ),
    Zn UMETA( DisplayName = "Zinc" ),
    Ga UMETA( DisplayName = "Gallium" ),
    Ge UMETA( DisplayName = "Germanium" ),
    As UMETA( DisplayName = "Arsenic" ),
    Se UMETA( DisplayName = "Selenium" ),
    Br UMETA( DisplayName = "Bromine" ),
    Kr UMETA( DisplayName = "Krypton" ),
    Rb UMETA( DisplayName = "Rubidium" ),
    Sr UMETA( DisplayName = "Strontium" ),
    Y  UMETA( DisplayName = "Yttrium" ),
    Zr UMETA( DisplayName = "Zirconium" ),
    Nb UMETA( DisplayName = "Niobium" ),
    Mo UMETA( DisplayName = "Molybdenum" ),
    Tc UMETA( DisplayName = "Technetium" ),
    Ru UMETA( DisplayName = "Ruthenium" ),
    Rh UMETA( DisplayName = "Rhodium" ),
    Pd UMETA( DisplayName = "Palladium" ),
    Ag UMETA( DisplayName = "Silver" ),
    Cd UMETA( DisplayName = "Cadmium" ),
    In UMETA( DisplayName = "Indium" ),
    Sn UMETA( DisplayName = "Tin" ),
    Sb UMETA( DisplayName = "Antimony" ),
    Te UMETA( DisplayName = "Tellurium" ),
    I  UMETA( DisplayName = "Iodine" ),
    Xe UMETA( DisplayName = "Xenon" ),
    Cs UMETA( DisplayName = "Cesium" ),
    Ba UMETA( DisplayName = "Barium" ),
    La UMETA( DisplayName = "Lanthanum" ),
    Ce UMETA( DisplayName = "Cerium" ),
    Pr UMETA( DisplayName = "Praseodymium" ),
    Nd UMETA( DisplayName = "Neodymium" ),
    Pm UMETA( DisplayName = "Promethium" ),
    Sm UMETA( DisplayName = "Samarium" ),
    Eu UMETA( DisplayName = "Europium" ),
    Gd UMETA( DisplayName = "Gadolinium" ),
    Tb UMETA( DisplayName = "Terbium" ),
    Dy UMETA( DisplayName = "Dysprosium" ),
    Ho UMETA( DisplayName = "Holmium" ),
    Er UMETA( DisplayName = "Erbium" ),
    Tm UMETA( DisplayName = "Thulium" ),
    Yb UMETA( DisplayName = "Ytterbium" ),
    Lu UMETA( DisplayName = "Lutetium" ),
    Hf UMETA( DisplayName = "Hafnium" ),
    Ta UMETA( DisplayName = "Tantalum" ),
    W  UMETA( DisplayName = "Wolfram" ),
    Re UMETA( DisplayName = "Rhenium" ),
    Os UMETA( DisplayName = "Osmium" ),
    Ir UMETA( DisplayName = "Iridium" ),
    Pt UMETA( DisplayName = "Platinum" ),
    Au UMETA( DisplayName = "Gold" ),
    Hg UMETA( DisplayName = "Mercury" ),
    Tl UMETA( DisplayName = "Thallium" ),
    Pb UMETA( DisplayName = "Lead" ),
    Bi UMETA( DisplayName = "Bismuth" ),
    Po UMETA( DisplayName = "Polonium" ),
    At UMETA( DisplayName = "Astatine" ),
    Rn UMETA( DisplayName = "Radon" ),
    Fr UMETA( DisplayName = "Francium" ),
    Ra UMETA( DisplayName = "Radium" ),
    Ac UMETA( DisplayName = "Actinium" ),
    Th UMETA( DisplayName = "Thorium" ),
    Pa UMETA( DisplayName = "Protactinium" ),
    U  UMETA( DisplayName = "Uranium" ),
    Np  UMETA( DisplayName = "Neptunium" ),
    Pu UMETA( DisplayName = "Plutonium" ),
    Am UMETA( DisplayName = "Americium" ),
    Cm UMETA( DisplayName = "Curium" ),
    Bk UMETA( DisplayName = "Berkelium" ),
    Cf UMETA( DisplayName = "Californium" ),
    Es UMETA( DisplayName = "Einsteinium" ),
    Fm UMETA( DisplayName = "Fermium" ),
    Md UMETA( DisplayName = "Mendelevium" ),
    No UMETA( DisplayName = "Nobelium" ),
    Lr UMETA( DisplayName = "Lawrencium" ),
    Rf UMETA( DisplayName = "Rutherfordium" ),
    Db UMETA( DisplayName = "Dubnium" ),
    Sg UMETA( DisplayName = "Seaborgium" ),
    Bh UMETA( DisplayName = "Bohrium" ),
    Hs UMETA( DisplayName = "Hassium" ),
    Mt UMETA( DisplayName = "Meitnerium" ),
    Ds UMETA( DisplayName = "Darmstadtium " ),
    Rg UMETA( DisplayName = "Roentgenium " ),
    Cn UMETA( DisplayName = "Copernicium " ),
    Nh UMETA( DisplayName = "Nihonium" ),
    Fl UMETA( DisplayName = "Flerovium" ),
    Mc UMETA( DisplayName = "Moscovium" ),
    Lv UMETA( DisplayName = "Livermorium" ),
    Ts UMETA( DisplayName = "Tennessine" ),
    Og UMETA( DisplayName = "Oganesson" )
};

/**
 * Define the range for enum iteration.
 */
ENUM_RANGE_BY_COUNT(EAtomicElement, EAtomicElement::Og);

/**
* Element symbol mappings to element names
*/
static TMap<EAtomicElement, FString> AtomicElements {
	{EAtomicElement::H, "Hydrogen"},
	{EAtomicElement::He, "Helium"},
	{EAtomicElement::Li, "Lithium"},
	{EAtomicElement::Be, "Beryllium"},
	{EAtomicElement::B, "Boron"},
	{EAtomicElement::C, "Carbon"},
	{EAtomicElement::N, "Nitrogen"},
	{EAtomicElement::O, "Oxygen"},
	{EAtomicElement::F, "Fluorine"},
	{EAtomicElement::Ne, "Neon"},
	{EAtomicElement::Na, "Sodium"},
	{EAtomicElement::Mg, "Magnesium"},
	{EAtomicElement::Al, "Aluminum"},
	{EAtomicElement::Si, "Silicon"},
	{EAtomicElement::P, "Phosphorus"},
	{EAtomicElement::S, "Sulfur"},
	{EAtomicElement::Cl, "Chlorine"},
	{EAtomicElement::Ar, "Argon"},
	{EAtomicElement::K, "Potassium"},
	{EAtomicElement::Ca, "Calcium"},
	{EAtomicElement::Sc, "Scandium"},
	{EAtomicElement::Ti, "Titanium"},
	{EAtomicElement::V, "Vanadium"},
	{EAtomicElement::Cr, "Chromium"},
	{EAtomicElement::Mn, "Manganese"},
	{EAtomicElement::Fe, "Iron"},
	{EAtomicElement::Co, "Cobalt"},
	{EAtomicElement::Ni, "Nickel"},
	{EAtomicElement::Cu, "Copper"},
	{EAtomicElement::Zn, "Zinc"},
	{EAtomicElement::Ga, "Gallium"},
	{EAtomicElement::Ge, "Germanium"},
	{EAtomicElement::As, "Arsenic"},
	{EAtomicElement::Se, "Selenium"},
	{EAtomicElement::Br, "Bromine"},
	{EAtomicElement::Kr, "Krypton"},
	{EAtomicElement::Rb, "Rubidium"},
	{EAtomicElement::Sr, "Strontium"},
	{EAtomicElement::Y,  "Yttrium"},
	{EAtomicElement::Zr, "Zirconium"},
	{EAtomicElement::Nb, "Niobium"},
	{EAtomicElement::Mo, "Molybdenum"},
	{EAtomicElement::Tc, "Technetium"},
	{EAtomicElement::Ru, "Ruthenium"},
	{EAtomicElement::Rh, "Rhodium"},
	{EAtomicElement::Pd, "Palladium"},
	{EAtomicElement::Ag, "Silver"},
	{EAtomicElement::Cd, "Cadmium"},
	{EAtomicElement::In, "Indium"},
	{EAtomicElement::Sn, "Tin"},
	{EAtomicElement::Sb, "Antimony"},
	{EAtomicElement::Te, "Tellurium"},
	{EAtomicElement::I, "Iodine"},
	{EAtomicElement::Xe, "Xenon"},
	{EAtomicElement::Cs, "Cesium"},
	{EAtomicElement::Ba, "Barium"},
	{EAtomicElement::La, "Lanthanum"},
	{EAtomicElement::Ce, "Cerium"},
	{EAtomicElement::Pr, "Praseodymium"},
	{EAtomicElement::Nd, "Neodymium"},
	{EAtomicElement::Pm, "Promethium"},
	{EAtomicElement::Sm, "Samarium"},
	{EAtomicElement::Eu, "Europium"},
	{EAtomicElement::Gd, "Gadolinium"},
	{EAtomicElement::Tb, "Terbium"},
	{EAtomicElement::Dy, "Dysprosium"},
	{EAtomicElement::Ho, "Holmium"},
	{EAtomicElement::Er, "Erbium"},
	{EAtomicElement::Tm, "Thulium"},
	{EAtomicElement::Yb, "Ytterbium"},
	{EAtomicElement::Lu, "Lutetium"},
	{EAtomicElement::Hf, "Hafnium"},
	{EAtomicElement::Ta, "Tantalum"},
	{EAtomicElement::W, "Wolfram"},
	{EAtomicElement::Re, "Rhenium"},
	{EAtomicElement::Os, "Osmium"},
	{EAtomicElement::Ir, "Iridium"},
	{EAtomicElement::Pt, "Platinum"},
	{EAtomicElement::Au, "Gold"},
	{EAtomicElement::Hg, "Mercury"},
	{EAtomicElement::Tl, "Thallium"},
	{EAtomicElement::Pb, "Lead"},
	{EAtomicElement::Bi, "Bismuth"},
	{EAtomicElement::Po, "Polonium"},
	{EAtomicElement::At, "Astatine"},
	{EAtomicElement::Rn, "Radon"},
	{EAtomicElement::Fr, "Francium"},
	{EAtomicElement::Ra, "Radium"},
	{EAtomicElement::Ac, "Actinium"},
	{EAtomicElement::Th, "Thorium"},
	{EAtomicElement::Pa, "Protactinium"},
	{EAtomicElement::U, "Uranium"},
	{EAtomicElement::Np, "Neptunium"},
	{EAtomicElement::Pu, "Plutonium"},
	{EAtomicElement::Am, "Americium"},
	{EAtomicElement::Cm, "Curium"},
	{EAtomicElement::Bk, "Berkelium"},
	{EAtomicElement::Cf, "Californium"},
	{EAtomicElement::Es, "Einsteinium"},
	{EAtomicElement::Fm, "Fermium"},
	{EAtomicElement::Md, "Mendelevium"},
	{EAtomicElement::No, "Nobelium"},
	{EAtomicElement::Lr, "Lawrencium"},
	{EAtomicElement::Rf, "Rutherfordium"},
	{EAtomicElement::Db, "Dubnium"},
	{EAtomicElement::Sg, "Seaborgium"},
	{EAtomicElement::Bh, "Bohrium"},
	{EAtomicElement::Hs, "Hassium"},
	{EAtomicElement::Mt, "Meitnerium"},
	{EAtomicElement::Ds, "Darmstadtium"},
	{EAtomicElement::Rg, "Roentgenium"},
	{EAtomicElement::Cn, "Copernicium"},
	{EAtomicElement::Nh, "Nihonium"},
	{EAtomicElement::Fl, "Flerovium"},
	{EAtomicElement::Mc, "Moscovium"},
	{EAtomicElement::Lv, "Livermorium"},
	{EAtomicElement::Ts, "Tennessine"},
	{EAtomicElement::Og, "Oganesson"}
};

/**
 * Result of an SDF string array parse.
 */
UENUM(BlueprintType)
enum class ESDFParseResult : uint8 {
	Success UMETA( DisplayName = "Success" ),
	ValidWithErrors UMETA( DisplayName = "Valid with errors" ),
	Empty UMETA( DisplayName = "Empty" ),
	Invalid UMETA( DisplayName = "Validation error" ),
	AtomsMismatch UMETA( DisplayName = "Atoms list length mismatch with count" ),
	BondsMismatch UMETA( DisplayName = "Bonds list length mismatch with count" )
};

/**
 * Atomic charge. Comments display the typical mappings from raw text to values.
 */
UENUM(BlueprintType)
enum class EAtomCharge : uint8 {
	Minus_3 UMETA( DisplayName = "-3" ), // 7
    Minus_2 UMETA( DisplayName = "-2" ), // 6
	Minus_1 UMETA( DisplayName = "-1" ), // 5
    Neutral UMETA( DisplayName = "Neutral" ), // 0
	Plus_1 UMETA( DisplayName = "+1" ), // 3
	Plus_2 UMETA( DisplayName = "+2" ), // 2
	Plus_3 UMETA( DisplayName = "+3" ), // 1
	Doublet_Radical UMETA( DisplayName = "Doublet Radical" ) // 4
};

/**
* Bond type. Comments display the typical mappings from raw text to values.
*/
UENUM(BlueprintType)
enum class EBondType : uint8 {
    Single UMETA( DisplayName = "Single" ), // 1
    Double UMETA( DisplayName = "Double" ), // 2
    Triple UMETA( DisplayName = "Triple" ), // 3
    Aromatic UMETA( DisplayName = "Aromatic" ), // 4
	Other UMETA( DisplayName = "Other" ) // None of the above
};

/**
* Bond stereoscopy. Comments display the typical mappings from raw text to values.
*/
UENUM(BlueprintType)
enum class EBondStereoscopy : uint8 {
	None UMETA( DisplayName = "Not Stereo" ), // 0
    Up UMETA( DisplayName = "Up" ), // 1
    Down UMETA( DisplayName = "Down" ), // 6
    Other UMETA( DisplayName = "Other" ) // None of the above
};

/**
* Atom property for charge and isotope types. 
* Comments display the typical mappings from raw text to values.
*/
UENUM(BlueprintType)
enum class EAtomProperty : uint8 {
	Charge UMETA( DisplayName = "Charge" ), // "CHG"
    Isotope UMETA( DisplayName = "Isotope" ), // "ISO"
};

/**
 * A single atom structure, including any additional attributes parsed from the properties block.
 */
USTRUCT(BlueprintType)
struct FAtom
{
	GENERATED_BODY()

	// This is measured in Angstroms. Will need to be scaled up when rendered.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Position;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EAtomicElement Element;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Symbol;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MassDifference;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EAtomCharge Charge;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EAtomProperty, int32> Properties;

	FAtom(): Position(FVector()), Element(), MassDifference(0), Charge(EAtomCharge::Neutral) {}

	FAtom(const FVector Position, const EAtomicElement AtomicSymbol, const int32 MassDifference, const EAtomCharge Charge) {
		this->Position = Position;
		this->Element = AtomicSymbol;
		this->MassDifference = MassDifference;
		this->Charge = Charge;
	}
};

/**
* Description of a single bond, including linkage, bond type and stereoscopy.
*/
USTRUCT(BlueprintType)
struct FBond
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntPoint AtomIndices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBondType BondType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBondStereoscopy Stereoscopy;

	FBond(): AtomIndices(FIntPoint()), BondType(), Stereoscopy() {}

	FBond(const FIntPoint AtomIndices, const EBondType BondType, const EBondStereoscopy Stereoscopy) {
		this->AtomIndices = AtomIndices;
		this->BondType = BondType;
		this->Stereoscopy = Stereoscopy;
	}
};

/**
 * Fully inclusive structure of a single molecule.
 */
USTRUCT(BlueprintType)
struct FMolecule
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Originator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Comment;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Version;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bChiral;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FAtom> Atoms;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FBond> Bonds;

	FMolecule(): bChiral(false) {
	}
};