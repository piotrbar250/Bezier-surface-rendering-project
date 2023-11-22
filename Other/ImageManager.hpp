#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Bitmap.hpp"
#include "global.hpp"
#include <cmath>

using namespace std;
using namespace sf;

// /../Backgrounds/background1.png
//./../Normal maps/normal_map1.png
class ImageManager
{
public:
    static void loadImage(string path = "./../Backgrounds/background1.png", Color array[W][H] = bitmap.background)
    {
        Image normalmap;
        if(!normalmap.loadFromFile(path))
        {
            cout << "Image not found" << endl;
        }

        int width = normalmap.getSize().x;
        int height = normalmap.getSize().y;


        for(int y = 0; y < H; y++)
            for(int x = 0; x < W; x++)
            {
                array[x][y] = normalmap.getPixel(x % width, y % height);
            }
    }

    static Point3d colorToVector(Color color)
    {
        // cout << "color " << color.g << endl;
        return Point3d{
            float(color.r) / 255.0f,
            float(color.g) / 255.0f,
            float(color.b) / 255.0f
        };
    }


    // static Point3d colorToVector(Color color)
    // {
    //     // cout << "color " << color.g << endl;
    //     return Point3d{
    //         float(color.r) / 255.0f,
    //         float(color.g) / 255.0f,
    //         float(color.b) / 255.0f
    //     };
    // }

    // static void applyNormalmap()
    // {
    //     float matrix[3][3] 
    //     Point3d det = cross([bitm, {0,0,1})
    // }
};