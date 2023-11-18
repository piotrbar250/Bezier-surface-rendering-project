#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

namespace Math
{
    class Point3d
    {
        public:
        float x, y, z;
        
    };

    int binomialCoeff(int n, int k)
    {
        int res = 1;

        if (k > n - k)
            k = n - k;

        for (int i = 0; i < k; ++i)
        {
            res *= (n - i);
            res /= (i + 1);
        }
        return res;
    }

    int binomial_3[4] = {1, 3, 3, 1};

    int binomial(int k)
    {
        if (k >= 0 && k < 4)
            return binomial_3[k];
        else
            return 0;
    }

    float power(float a, int b)
    {
        if (b < 0 || b > 3)
        {
            cout << "Exponent out of allowed range (0-3)." << endl;
            return -1;
        }

        switch (b)
        {
        case 0:
            return 1;
        case 1:
            return a;
        case 2:
            return a * a;
        case 3:
            return a * a * a;
        default:
        {
            cout << "error" << endl;
            return -1;
        }
        }
    }

};