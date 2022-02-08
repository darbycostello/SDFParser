#pragma once

#include "CoreMinimal.h"
#include "SDFParserStructs.h"
#include "Engine/DataAsset.h"
#include "SDFConfig.generated.h"

/**
 * Data asset class, used to configure various options for displaying SDF-parsed molecule data. 
 */
UCLASS()
	class USDFConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Atoms")
	FColor DefaultAtomColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Atoms")
	TMap<EAtomicElement, FColor> AtomColors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Atoms")
	float DefaultRenderScale;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonds")
	FColor DefaultBondColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonds")
	TMap<EBondType, FColor> BondColors;
};