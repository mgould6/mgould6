#pragma once

#include <vector>
#include "PerlinNoiseGenerator.h"

class NoiseMapGenerator
{
public:
    NoiseMapGenerator(int width, int length, int height, PerlinNoiseGenerator& noiseGenerator);
    std::vector<std::vector<std::vector<float>>> GenerateNoiseMap();

private:
    int _width;
    int _length;
    int _height;
    PerlinNoiseGenerator& _noiseGenerator;
};
