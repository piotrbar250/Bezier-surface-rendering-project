#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Math.hpp"
#include "global.hpp"
#include "PolygonInterior.hpp"
#include "TriangleMeshProcessor.hpp"

using namespace std;
using namespace sf;

class ControlPoints
{
public: 
    Bezier &bezier;
    TriangleMeshProcessor& triangleMeshProcessor;
    vector<Point> points = {
        {10, 20},
        {260, 20},
        {528, 20},
        {777, 20},

        {10, 260},
        {260, 260},
        {528, 260},
        {777, 260},

        {10, 528},
        {260, 528},
        {528, 528},
        {777, 528},

        {10, 797},
        {260, 797},
        {528, 797},
        {777, 797}
    };

    map<pair<int,int>, float*> dictionary;

    ControlPoints(Bezier &bezier, TriangleMeshProcessor& triangleMeshProcessor) : bezier(bezier), triangleMeshProcessor(triangleMeshProcessor)
    {
        dictionary[{10, 20}] = &(bezier.Z[0][0]);
        dictionary[{260, 20}] = &(bezier.Z[1][0]);
        dictionary[{528, 20}] = &(bezier.Z[2][0]);
        dictionary[{777, 20}] = &(bezier.Z[3][0]);

        dictionary[{10, 260}] = &(bezier.Z[0][1]);
        dictionary[{260, 260}] = &(bezier.Z[1][1]);
        dictionary[{528, 260}] = &(bezier.Z[2][1]);
        dictionary[{777, 260}] = &(bezier.Z[3][1]);

        dictionary[{10, 528}] = &(bezier.Z[0][2]);
        dictionary[{260, 528}] = &(bezier.Z[1][2]);
        dictionary[{528, 528}] = &(bezier.Z[2][2]);
        dictionary[{777, 528}] = &(bezier.Z[3][2]);

        dictionary[{10, 797}] = &(bezier.Z[0][3]);
        dictionary[{260, 797}] = &(bezier.Z[1][3]);
        dictionary[{528, 797}] = &(bezier.Z[2][3]);
        dictionary[{777, 797}] = &(bezier.Z[3][3]); 
    }

    void handleEvent(const Event &event)
    {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            cout << "sprawdzam" << endl;
                CircleShape circle(10);
                circle.setPosition(10, H-20);
                if(circle.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    cout << "yeah" << endl;
                }

            for(Point p: points)
            {
                int x = p.x;
                int y = p.y;

                CircleShape circle(10);
                circle.setPosition(x, H-y);
                if(circle.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    *(dictionary[{x, y}]) = offsetThickness;
                    triangleMeshProcessor.processFrame(true, false);
                    // cout << x << " " << y <<
                }
            }
        }
    }
};