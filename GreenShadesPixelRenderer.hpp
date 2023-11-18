#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "PixelRenderer.hpp"
#include <iostream>

using namespace std;
using namespace sf;

class GreenShadesPixelRenderer : public PixelRenderer
{
public:
    GreenShadesPixelRenderer(Bezier &bezier, LightSource& lightSource) : PixelRenderer(bezier, lightSource) {}

    virtual void setColors() override
    {
        int index = 0;
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                points[index++].color = Color(0, bitmap.height[x][y] / 2.0f * 255, 0);
    }
};