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
    Point3d vector;

    LightSource() : LightSource(0.5) {}

    LightSource(float z ) : originX(W/2), originY(H/2), z(z), radius(450), angle(-0.05f){}

    void adjustPosition()
    {
        x = radius * cos(angle) + originX;
        y = radius * sin(angle) + originY;

        vector = {x / float(W), y / float(H), z};
    }

    void nextFrame()
    {
        angle += 0.01f;
    }
};