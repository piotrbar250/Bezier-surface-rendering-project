#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Bitmap.hpp"
#include "LightSource.hpp"
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
    LightSource &lightSource;

    PixelRenderer(Bezier &bezier, LightSource &lightSource) : bezier(bezier), lightSource(lightSource)
    {
        prepPoints();
    }

    void prepPoints()
    {
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                points.push_back(Vector2f(x, H-y));
    }

    virtual void setColors()
    {
        int index = 0;
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                points[index++].color = bitmap.color[x][y];
    }
    
    void drawLightSource()
    {
        lightSource.nextFrame();
        lightSource.adjustPosition();

        CircleShape circle(5);
        circle.setFillColor(Color::Yellow);
        circle.setPosition(lightSource.x, H-lightSource.y);
        window.draw(circle);
    }

    void draw()
    {
        setColors();
        window.draw(&points[0], points.size(), sf::Points);
        drawLightSource();
    }
};