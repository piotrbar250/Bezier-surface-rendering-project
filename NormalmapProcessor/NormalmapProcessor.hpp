#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Bitmap.hpp"
#include "global.hpp"
#include "ImageManager.hpp"
#include <cmath>

class NormalmapProcessor
{
public: 

    static void apply(string path="./../Normal maps/normal_map3.png")
    {
        ImageManager::loadImage(path, bitmap.normalmap);

        float matrix[3][3];

        for(int y = 0; y < H; y++)
            for(int x = 0; x < W; x++)
            {
             
                Point3d surfaceVector = bitmap.N[x][y].normalized();
                Point3d normmalmapVector = ImageManager::colorToVector(bitmap.normalmap[x][y]).normalized();

                // normmalmapVector = Point3d(0.2784314,  0.60784316,  0.5568628);

                Point3d B, T;

                if(surfaceVector == Point3d(0, 0, 1))
                    B = {0, 1, 0};
                else
                    B = cross(surfaceVector, Point3d(0, 0, 1)).normalized();

                T = cross(B, surfaceVector).normalized();

                matrix[0][0] = T.x; 
                matrix[1][0] = T.y; 
                matrix[2][0] = T.z;

                matrix[0][1] = B.x; 
                matrix[1][1] = B.y; 
                matrix[2][1] = B.z;

                matrix[0][2] = surfaceVector.x; 
                matrix[1][2] = surfaceVector.y; 
                matrix[2][2] = surfaceVector.z;

                // cout << "stary: " << bitmap.N[x][y] << endl;
                bitmap.N[x][y] = normmalmapVector * matrix;

                if(x == 200 && y == 250)
                {
                    cout << "surfaceVector " << surfaceVector << endl;
                    // cout << "normalmapVector " << normmalmapVector << endl;
                    // cout << "B " << B << endl;
                    // cout << "T " << T << endl;

                    for(int i = 0; i < 3; i++)
                    {
                        for(int j = 0; j < 3; j++)
                        {

                        }
                    }

                    cout << "wynik " << bitmap.N[x][y] << endl << endl;
                }
                // cout << surfaceVector - bitmap.N[x][y] << endl;
                // exit(1);

                // cout << "nowy " << bitmap.N[x][y] << endl << endl;
                // bitmap.N[x][y] = normmalmapVector.normalized();
            }
    } 
};