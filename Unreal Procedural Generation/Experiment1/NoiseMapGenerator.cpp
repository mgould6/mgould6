#include "NoiseMapGenerator.h"

NoiseMapGenerator::NoiseMapGenerator(int width, int length, int height, PerlinNoiseGenerator& noiseGenerator)
    : _width(width), _length(length), _height(height), _noiseGenerator(noiseGenerator)
{
}

std::vector<std::vector<std::vector<float>>> NoiseMapGenerator::GenerateNoiseMap()
{
    std::vector<std::vector<std::vector<float>>> noiseMap(_width, std::vector<std::vector<float>>(_length, std::vector<float>(_height)));

    for (int x = 0; x < _width; ++x) {
        for (int y = 0; y < _length; ++y) {
            for (int z = 0; z < _height; ++z) {
                noiseMap[x][y][z] = _noiseGenerator.GeneratePerlinNoise(x, y, z);
            }
        }
    }

    return noiseMap;
}
