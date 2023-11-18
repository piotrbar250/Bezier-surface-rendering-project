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
    GreenShadesPixelRenderer(Bezier &bezier) : PixelRenderer(bezier) {}

    virtual void setColors() override
    {
        int index = 0;
        for (int x = 0; x < M; x++)
            for (int y = 0; y < N; y++)
                points[index++].color = Color(0, bitmap.heights[x][y] / 2.0f * 255, 0);
    }
};