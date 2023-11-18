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

    void draw()
    {
        if(true) // here goes a condtition for changing control points
            setHeights();
        
        for(int i = 0; i < points.size(); i++)
            points[i].color = Color(0, heights[i]/2.0f * 255, 0);

        window.draw(&points[0], points.size(), sf::Points);
    }
};