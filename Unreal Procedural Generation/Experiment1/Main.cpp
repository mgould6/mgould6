#include "Main.h"
#include "Terrain.h"

int main()
{
    int width = 100;
    int length = 100;
    int height = 100;

    Terrain terrain(width, length, height);
    terrain.GenerateTerrain();

    // The terrainMap variable now holds the generated 3D terrain map
    auto terrainMap = terrain.GetTerrainMap();

    return 0;
}
