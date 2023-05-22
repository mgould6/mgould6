#pragma once

#include "CoreMinimal.h"
#include "Terrain.h"

#include "TerrainInterface.generated.h"
// Forward declaration of your terrain class
class Terrain;

UCLASS(BlueprintType)
class EXPERIMENT1_API UTerrainInterface : public UObject
{
    GENERATED_BODY()

public:
    UTerrainInterface();

    UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
    void GenerateTerrain();

    UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
    TArray<float> GetTerrainData();

    UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
    int32 GetWidth();

    UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
    int32 GetLength();

    UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
    int32 GetHeight();

private:
    TUniquePtr<Terrain> TerrainInstance;
};
