#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Bitmap.hpp"
#include "PhongReflectionProcessor.hpp"

class FramePixelProcessor
{
public:

    Bezier& bezier;
    PhongReflectionProcessor& prp;
    FramePixelProcessor(Bezier &bezier, PhongReflectionProcessor& prp) : bezier(bezier), prp(prp){}

    void calculateNormalVectors()
    {
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                bitmap.N[x][y] = cross(bezier.tangentX(bitmap.xPoints[x], bitmap.yPoints[y]),
                                        bezier.tangentY(bitmap.xPoints[x], bitmap.yPoints[y])).normalized();
    }

    void calculateHeights()
    {
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                bitmap.height[x][y] = bezier.z(bitmap.xPoints[x], bitmap.yPoints[y]);
        calculateNormalVectors();
    }

    void calculateColors()
    {   
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                bitmap.color[x][y] = prp.computePixelColor(x, y);
    }
};