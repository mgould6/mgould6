#pragma once

#include <vector>
#include "PerlinNoiseGenerator.h"
#include "NoiseMapGenerator.h"

class Terrain
{
public:
    Terrain(int width, int length, int height);
    void GenerateTerrain();
    std::vector<std::vector<std::vector<float>>> GetTerrainMap();
    int GetWidth();
    int GetLength();
    int GetHeight();

private:
    int _width;
    int _length;
    int _height;
    PerlinNoiseGenerator _perlinNoise;
    NoiseMapGenerator _noiseMapGenerator;
    std::vector<std::vector<std::vector<float>>> _terrainMap;
};
