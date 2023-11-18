#pragma once
#include <SFML/Graphics.hpp>
#include "Math.hpp"

// const int N = 720, M = 1152;
const int N = 1000, M = 1000;

// class Point3d
// {
// public:
//     float x, y, z;
    
// };

class Bitmap
{
public:
    float heights[M][N];
    Color colors[M][N];

    Bitmap()
    {

    }  
};