#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Bitmap.hpp"
#include "global.hpp"
#include "ImageManager.hpp"
#include <cmath>

class BackgroundProcessor
{
public: 

    static void load(string path="./../Backgroundd/background1.png")
    {
        background = true;
        ImageManager::loadImage(path, bitmap.background);
    } 
    static void hide()
    {
        background = false;
        ImageManager::loadImage(path, bitmap.background);
    } 
    
};