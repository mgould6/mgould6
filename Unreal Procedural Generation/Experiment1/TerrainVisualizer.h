#pragma once

#include "CoreMinimal.h"
#include "TerrainInterface.h"
#include "Landscape.h"
#include "TerrainVisualizer.generated.h"

UCLASS()
class EXPERIMENT1_API ATerrainVisualizer : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATerrainVisualizer();

    // Reference to the terrain data asset
    UPROPERTY(EditAnywhere, Category = "Terrain")
        UTerrainInterface* TerrainDataAsset;

    // References to the landscape actors
    UPROPERTY(VisibleAnywhere, Category = "Terrain")
        TArray<ALandscape*> LandscapeActors;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Load and apply the terrain data to the landscape
    UFUNCTION(BlueprintCallable, Category = "Terrain")
        void LoadAndApplyTerrainData();
};
