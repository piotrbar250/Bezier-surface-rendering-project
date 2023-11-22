#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Bitmap.hpp"
#include "Bezier.hpp"
#include "LightSource.hpp"
#include "ImageManager.hpp"

#include <chrono>
#include <thread>

class PhongReflectionProcessor
{
public:
    Bezier& bezier;
    LightSource& lightSource;
    float kd = 0.5, ks = 0.5;
    Point3d Il = {1,1,1}, Io = {0,0,1};
    Point3d N, L;
    Point3d V = {0, 0, 1}, R;
    float m = 1;
    
    PhongReflectionProcessor(Bezier& bezier, LightSource& lightSource) : bezier(bezier), lightSource(lightSource) {}

    Color computePixelColor(int x, int y)
    {   
        // Io = ImageManager::colorToVector(bitmap.background[x][y]);
        // cout << Io << endl;
        N = bitmap.N[x][y];
        
        L = lightSource.vector - Point3d(bitmap.xPoints[x], bitmap.yPoints[y], bitmap.height[x][y]);
        L = L.normalized();

        R = N * 2 * max(0.0f, dot(N, L)) - L;
        R = R.normalized();

        float cos_V_R = max(0.0f, dot(V,R));

        Point3d Ip = Il * Io * kd * max(0.0f, dot(N, L));

        Ip = Ip + Il * Io * ks * pow(cos_V_R, m);

        return Color(Ip.x*255, Ip.y*255, Ip.z*255);
    }
};
