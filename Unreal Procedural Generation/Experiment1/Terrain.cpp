#include "Terrain.h"
#include <memory>

Terrain::Terrain(int width, int length, int height)
    : _width(width), _length(length), _height(height), _perlinNoise(), _noiseMapGenerator(width, length, height, _perlinNoise)
{
}

void Terrain::GenerateTerrain()
{
    _terrainMap = _noiseMapGenerator.GenerateNoiseMap();
}

std::vector<std::vector<std::vector<float>>> Terrain::GetTerrainMap()
{
    return _terrainMap;
}

int Terrain::GetWidth()
{
    return _width;
}

int Terrain::GetLength()
{
    return _length;
}

int Terrain::GetHeight()
{
    return _height;
}
