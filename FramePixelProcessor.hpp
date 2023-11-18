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
        for (int x = 0; x < M; x++)
            for (int y = 0; y < N; y++)
                bitmap.heights[x][y] = bezier.z(float(x) / float(M), float(y) / float(N));
    }

    void calculateColors()
    {
        /*
            TODO
        */

         for (int x = 0; x < M; x++)
            for (int y = 0; y < N; y++)
                bitmap.colors[x][y] = Color::Red;
    }
};