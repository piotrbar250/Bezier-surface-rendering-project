#pragma once
#include <SFML/Graphics.hpp>
#include "Math.hpp"

// const int H = 720, W = 1152;
const int W = 1000, H = 1000;

class Bitmap
{
public:
    // this represents points in the cartesian system

    /*
    These are points stored in the Bitmap
    03 13 23 33
    02 12 22 32
    01 11 21 31
    00 10 20 30
    */

    float height[W][H];
    Color color[W][H];

    Bitmap() {}
};