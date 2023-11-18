#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Math.hpp"
#include "global.hpp"


using namespace std;
using namespace sf;
using namespace Math;

class Bezier
{
public:

    float Z[4][4];
    int prepZ[4][4] = {
        {2,0,0,2},
        {0,0,0,0},
        {0,0,2,0},
        {0,0,0,0}
    };    
    /*
        prepZ visualizes control points


        Z - control points:

        z03 z13 z23 z33
        z02 z12 z22 z32
        z01 z11 z21 z31
        z00 z10 z20 z30
    */

    void genZ()
    {
        // for(int i = 0; i < 4; i++)
        //     for(int j = 0; j < 4; j++)
        //         Z[j][4-i-1] = prepZ[i][j];      

        // for(int i = 0; i < 4; i++)
        //     for(int j = 0; j < 4; j++)
        //         Z[i][j] = prepZ[i][j];

        for(int k = 0; k < 4; k++)
            Z[k][0] = prepZ[3][k]; 
        for(int k = 0; k < 4; k++)
            Z[k][1] = prepZ[2][k]; 
        for(int k = 0; k < 4; k++)
            Z[k][2] = prepZ[1][k];  
        for(int k = 0; k < 4; k++)
            Z[k][3] = prepZ[0][k];  
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

    Point3d tangentX(float u, float v)
    {
        // int n = 3, m = 3;

        // float value = 0;
        // for(int i = 0; i <= n-1; i++)
        //     for(int j = 0; j <= m; j++)
        //         value += (Z[i+1], )
    }
};