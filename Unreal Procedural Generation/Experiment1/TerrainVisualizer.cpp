#include "TerrainVisualizer.h"
#include "Kismet/GameplayStatics.h"
#include "LandscapeEdit.h"
#include "EngineUtils.h" // Include this header for TActorIterator

// Sets default values
ATerrainVisualizer::ATerrainVisualizer()
{
    PrimaryActorTick.bCanEverTick = true;
    TerrainDataAsset = nullptr;
}

// Called when the game starts or when spawned
void ATerrainVisualizer::BeginPlay()
{
    Super::BeginPlay();

    for (TActorIterator<ALandscape> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        LandscapeActors.Add(*ActorItr);
    }

    if (TerrainDataAsset && LandscapeActors.Num() > 0)
    {
        LoadAndApplyTerrainData();
    }
}

// Called every frame
void ATerrainVisualizer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ATerrainVisualizer::LoadAndApplyTerrainData()
{
    auto TerrainData = TerrainDataAsset->GetTerrainData();

    if (TerrainData.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("TerrainData is empty."));
        return;
    }

    // Initialize minVal and maxVal with the first value of the TerrainData
    float minVal = TerrainData[0];
    float maxVal = TerrainData[0];

    // Loop through each value in the TerrainData
    for (auto& val : TerrainData)
    {
        // Update minVal and maxVal as needed
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
    }

    float range = maxVal - minVal;

    int32 Width = 100;
    int32 Height = 100;

    // Create grayscale image from terrain data
    TArray<uint8> image;
    image.Reserve(Width * Height);
    for (const auto& val : TerrainData)
    {
        uint8 pixelValue = static_cast<uint8>((val - minVal) / range * 255); // Convert normalized value to pixel intensity
        image.Add(pixelValue);
    }
    // Asynchronously save image as .RAW file
    FString FileName = FPaths::ProjectDir() + "/TerrainHeightmap.raw";
    if (!FFileHelper::SaveArrayToFile(image, *FileName))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to write to file: %s"), *FileName);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("File saved successfully: %s"), *FileName);

        // Load .RAW file
        TArray<uint8> RawData;
        if (!FFileHelper::LoadFileToArray(RawData, *FileName))
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to read file: %s"), *FileName);
            return;
        }

        // Convert the raw data to height data
        TArray<uint16> HeightData;
        HeightData.Reserve(RawData.Num() / 2);
        for (int32 i = 0; i < RawData.Num(); i += 2)
        {
            uint16 PixelValue = ((uint16)RawData[i] << 8) | RawData[i + 1];
            HeightData.Add(PixelValue);
        }

        // Asynchronously apply the height data to the landscape on the game thread
        // Asynchronously apply the height data to the landscape on the game thread
        Async(EAsyncExecution::TaskGraphMainThread, [this, HeightData = MoveTemp(HeightData), Width, Height]()
            {
                for (ALandscape* LandscapeActor : LandscapeActors) {
                    if (LandscapeActor)
                    {
                        FLandscapeEditDataInterface LandscapeEditDataInterface(LandscapeActor->GetLandscapeInfo());

                        int32 X1 = 0;
                        int32 Y1 = 0;
                        int32 X2 = Width - 1;
                        int32 Y2 = Height - 1;
                        const uint16* InData = HeightData.GetData();
                        int32 InStride = 0;
                        bool InCalcNormals = true;
                        const uint16* InNormalData = nullptr;
                        const uint16* InHeightAlphaBlendData = nullptr;
                        const uint8* InHeightRaiseLowerData = nullptr;
                        bool InCreateComponents = false;
                        UTexture2D* InHeightmap = nullptr;
                        UTexture2D* InXYOffsetmapTexture = nullptr;
                        bool InUpdateBounds = true;
                        bool InUpdateCollision = true;
                        bool InGenerateMips = true;

                        LandscapeEditDataInterface.SetHeightData(
                            X1, Y1, X2, Y2, InData, InStride,
                            InCalcNormals, InNormalData, InHeightAlphaBlendData,
                            InHeightRaiseLowerData, InCreateComponents, InHeightmap,
                            InXYOffsetmapTexture, InUpdateBounds, InUpdateCollision, InGenerateMips
                        );
                    }
                }
                
            });

    }
}
