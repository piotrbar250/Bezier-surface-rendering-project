#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Bitmap.hpp"

class LightSource
{
public:
    float originX, originY;
    float x,y,z;
    float radius;
    float angle;
    LightSource() : LightSource(5) {}

    LightSource(float z ) : originX(M/2), originY(M/2), z(z), radius(100), angle(0.0f){}

    void adjustPosition()
    {
        x = radius * cos(angle) + originX;
        y = radius * sin(angle) + originY;
    }

    void nextFrame()
    {
        angle += 0.05f;
    }
};