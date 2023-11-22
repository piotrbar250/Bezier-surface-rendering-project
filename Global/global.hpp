#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Bitmap.hpp"
#include "Math.hpp"
using namespace std;
using namespace sf;


extern RenderWindow window;
extern Bitmap bitmap;
bool debug = false;

bool background = false;

Math::Point3d IO_COLOR = {0, 0, 1};