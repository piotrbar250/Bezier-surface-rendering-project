#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Bitmap.hpp"
#include <iostream>

using namespace std;
using namespace sf;

class PixelRenderer
{
public:
    static int cnt;
    vector<Vertex> points;
    vector<float> heights;
    vector<Color> colors;
    Bezier &bezier;

    PixelRenderer(Bezier &bezier) : bezier(bezier)
    {
        prepPoints();
    }

    void prepPoints()
    {
        for (int x = 0; x < M; x++)
            for (int y = 0; y < N; y++)
            {
                points.push_back(Vector2f(x, N - y));
                heights.push_back(bezier.z(float(x) / float(M), float(y) / float(N)));
            }
    }

    void setHeights()
    {
        int index = 0;
        for (int x = 0; x < M; x++)
            for (int y = 0; y < N; y++)
                heights[index++] = bitmap.heights[x][y];
    }

    void setColors()
    {
        int index = 0;
        for (int x = 0; x < M; x++)
            for (int y = 0; y < N; y++)
                colors[index++] = bitmap.colors[x][y];
    }

    void draw()
    {
        if(true) // here goes a condtition for changing control points
            setHeights();
        setColors();
        window.draw(&points[0], points.size(), sf::Points);
    }
};