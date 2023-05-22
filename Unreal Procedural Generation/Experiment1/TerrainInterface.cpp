#include "TerrainInterface.h"
#include "Terrain.h"

UTerrainInterface::UTerrainInterface()
{
    // Replace these values with whatever size you want your terrain to be
    int width = 100;
    int length = 100;
    int height = 100;
    
    // Create an instance of your Terrain class
    TerrainInstance = MakeUnique<Terrain>(width, length, height);
}

void UTerrainInterface::GenerateTerrain()
{
    if (TerrainInstance)
    {
        TerrainInstance->GenerateTerrain();
    }
}

TArray<float> UTerrainInterface::GetTerrainData()
{
    TArray<float> UnrealTerrainData;

    if (TerrainInstance)
    {
        // Convert your std::vector based terrain data to Unreal's TArray
        auto TerrainData = TerrainInstance->GetTerrainMap();
        for (const auto& X : TerrainData)
        {
            for (const auto& Y : X)
            {
                for (const auto& Z : Y)
                {
                    UnrealTerrainData.Add(Z);
                }
            }
        }
    }

    return UnrealTerrainData;
}

int32 UTerrainInterface::GetWidth()
{
    if (TerrainInstance)
    {
        return TerrainInstance->GetWidth();
    }
    return 0;
}

int32 UTerrainInterface::GetLength()
{
    if (TerrainInstance)
    {
        return TerrainInstance->GetLength();
    }
    return 0;
}

int32 UTerrainInterface::GetHeight()
{
    if (TerrainInstance)
    {
        return TerrainInstance->GetHeight();
    }
    return 0;
}
