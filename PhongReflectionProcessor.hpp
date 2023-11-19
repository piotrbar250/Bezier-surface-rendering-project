#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Bitmap.hpp"
#include "Bezier.hpp"
#include "LightSource.hpp"
//LambertianReflectanceProcessor

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
    Point3d R, V = {0, 0, 1};
    float m = 1;
    
    PhongReflectionProcessor(Bezier& bezier, LightSource& lightSource) : bezier(bezier), lightSource(lightSource)
    {

    }

    Color computePixelColor(float x, float y, float z)
    {
        bool debug = false;
        float debug_x = 0.75;
        float debug_y = 0.75;

        if(debug && x == debug_x and y == debug_y)
        {
            cout << endl << endl;
            cout << "x, y, z:  " << x << " " << y << " " << z << endl;
        }

        if(debug && x == debug_x and y == debug_y)
        {
            cout << endl << endl;
            cout << "pochodnay: " << bezier.tangentY(x, y) << endl;
        }


        N = cross(bezier.tangentX(x, y), bezier.tangentY(x, y));
        L = Point3d(float(lightSource.x)/float(W), float(lightSource.y)/float(H), lightSource.z) - Point3d(x, y, z);


        if(debug && x == debug_x and y == debug_y)
        {
            cout << endl << endl;
            cout << "N: " << N << endl;
            cout << "L " << L << endl;
        }

        // cout << lightSource.x << " " << lightSource.y << " " << lightSource.z << endl;

        if(debug && x == debug_x and y == debug_y)
        {
            cout << "Lightsource: " << float(lightSource.x)/float(W) << " " << float(lightSource.y)/float(H) << " " << lightSource.z << endl;
        }


        N = N.normalized(); 
        L = L.normalized();


        if(debug && x == debug_x and y == debug_y)
        {
            cout << endl << endl;
            cout << "N.norm: " << N << endl;
            cout << "L.norm " << L << endl;
        }

        // cout << N.x << " " << N.y << " " << N.z << endl;
        // cout << L.x << " " << L.y << " " << L.z << endl;

        R = N * 2 * max(0.0f, dot(N, L)) - L;
    
        R = R.normalized();
        Point3d Ip = Il * Io * kd * max(0.0f, dot(N, L));
        Ip = Ip + Il * Io * kd * max(0.0f, dot(V,R));

        // cout << Ip.y << endl;
 
        // if(x == 1 && y == 0)
        //     exit(1);

        if(debug && x == debug_x and y == debug_y)
        {
            cout << endl << endl;
            cout << "I: " << Ip << endl;
        }
        return Color(Ip.x*255, Ip.y*255, Ip.z*255);

    }
};

// PhongReflectionProcessor prp(ks = 3)