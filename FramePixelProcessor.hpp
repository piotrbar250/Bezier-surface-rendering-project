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

    void calculateHeights()
    {
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                bitmap.height[x][y] = bezier.z(float(x) / float(W), float(y) / float(H));

        cout << bitmap.height[250][250] << endl;
    }

    void calculateColors()
    {
        /*
            TODO
        */

        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                bitmap.color[x][y] = prp.computePixelColor(float(x) / float(W), float(y) / float(H), bitmap.height[x][y]);

        //  for (int y = 0; y < H; y++)
        //     for (int x = 0; x < W; x++)
        //         bitmap.color[x][y] = Color::Black;
    }
};