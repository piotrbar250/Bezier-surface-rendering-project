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
        {333, 20},
        {666, 20},
        {980, 20},

        {10, 333},
        {333, 333},
        {666, 333},
        {980, 333},

        {10, 666},
        {333, 666},
        {666, 666},
        {980, 666},

        {10, 999},
        {333, 999},
        {666, 999},
        {980, 999}
    };

    map<pair<int,int>, float*> dictionary;

    ControlPoints(Bezier &bezier, TriangleMeshProcessor& triangleMeshProcessor) : bezier(bezier), triangleMeshProcessor(triangleMeshProcessor)
    {
        dictionary[{10, 20}] = &(bezier.Z[0][0]);
        dictionary[{333, 20}] = &(bezier.Z[1][0]);
        dictionary[{666, 20}] = &(bezier.Z[2][0]);
        dictionary[{980, 20}] = &(bezier.Z[3][0]);

        dictionary[{10, 333}] = &(bezier.Z[0][1]);
        dictionary[{333, 333}] = &(bezier.Z[1][1]);
        dictionary[{666, 333}] = &(bezier.Z[2][1]);
        dictionary[{980, 333}] = &(bezier.Z[3][1]);

        dictionary[{10, 666}] = &(bezier.Z[0][2]);
        dictionary[{333, 666}] = &(bezier.Z[1][2]);
        dictionary[{666, 666}] = &(bezier.Z[2][2]);
        dictionary[{980, 666}] = &(bezier.Z[3][2]);

        dictionary[{10, 999}] = &(bezier.Z[0][3]);
        dictionary[{333, 999}] = &(bezier.Z[1][3]);
        dictionary[{666, 999}] = &(bezier.Z[2][3]);
        dictionary[{980, 999}] = &(bezier.Z[3][3]); 
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
                    cout << x << " " << y << endl;
                }
            }
        }
    }
};