#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Math.hpp"
#include "global.hpp"

using namespace std;
using namespace sf;

class Bezier
{
public:

    float Z[4][4];
    int prepZ[4][4] = {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {2,0,0,0}
    };    

    int prepZ2[4][4] = {
        {1,1,1,1},
        {1,1,0,1},
        {1,1,1,1},
        {1,1,1,1}
    };


    void genZ()
    {
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                Z[j][4-i-1] = prepZ[i][j];
    }


    Bezier()
    {
        genZ();
    }

    float B(int i, float argument) // bezierCoefficient
    {
        return Math::binomial(i) * Math::power(argument, i) * Math::power(1.0f - argument, 3 - i);
    }


    float z(float x, float y)
    {
        float value = 0;
        for(int i = 0; i <= 3; i++ )
            for(int j =0; j <= 3; j++)
            {
                value += (Z[i][j] * B(i, x) * B(j, y));
            }
        return value;
    }
};