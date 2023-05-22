#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TerrainDataAsset.generated.h"

UCLASS()
class EXPERIMENT1_API UTerrainDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
        int Width;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
        int Length;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
        int Height;

    // You may add more properties here according to your requirements
};
