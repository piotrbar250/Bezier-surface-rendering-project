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
        for (int x = 0; x < M; x++)
            for (int y = 0; y < N; y++)
                points.push_back(Vector2f(x, N - y));
    }

    virtual void setColors()
    {
        int index = 0;
        for (int x = 0; x < M; x++)
            for (int y = 0; y < N; y++)
                points[index++].color = bitmap.colors[y][x];
    }
    
    void drawLightSource()
    {
        // cout << "jestem" << endl;
        lightSource.nextFrame();
        lightSource.adjustPosition();

        // cout << lightSource.x << " " << lightSource.y << " " << endl;
        Vertex vertex(Vector2f(lightSource.x, N-lightSource.y), Color::White);
        // window.draw(&vertex, 1, sf::Points);

        CircleShape circle(5);
        circle.setFillColor(Color::Yellow);
        circle.setPosition(lightSource.x, lightSource.y);
        window.draw(circle);
    }

    void draw()
    {
        setColors();
        window.draw(&points[0], points.size(), sf::Points);
        drawLightSource();
    }
};