#pragma once

#include "CoreMinimal.h"

class PerlinNoiseGenerator
{
public:
    PerlinNoiseGenerator();

    // Generate Perlin Noise for the given coordinates
    float GeneratePerlinNoise(float x, float y, float z);

private:
    // Function to generate fade curve
    float Fade(float t);

    // Linear interpolation
    float Lerp(float a, float b, float t);

    // Gradient function
    float Grad(int hash, float x, float y, float z);

    static const int permutation[];
    int p[512];
};
