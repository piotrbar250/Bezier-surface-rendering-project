#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Bitmap.hpp"

class FramePixelProcessor
{
public:

Bezier& bezier;
    FramePixelProcessor(Bezier &bezier) : bezier(bezier){}

    void calculateHeights()
    {
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                bitmap.height[x][y] = bezier.z(float(x) / float(W), float(y) / float(H));
    }

    void calculateColors()
    {
        /*
            TODO
        */

         for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                bitmap.color[x][y] = Color::Black;
    }
};