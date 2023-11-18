#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include <iostream>

using namespace std;
using namespace sf;

class HeatMapPixelRenderer
{
public:
    static int cnt;
    vector<Vertex> points;
    vector<float> intensities;
    Bezier &bezier;

    HeatMapPixelRenderer(Bezier &bezier) : bezier(bezier)
    {
        prepPoints();
    }

    void prepPoints()
    {
        float maxh = -10;
        int mx=-1, my=-1;
        for (int x = 0; x < M; x++)
            for (int y = 0; y < N; y++)
            {
                points.push_back(Vector2f(x, N - y));
                intensities.push_back(bezier.z(float(x) / float(M), float(y) / float(N)));


                if(x == 250 && y == 250)
                {
                    cout << intensities.back() << endl;
                }
                if(intensities.back() > maxh)
                {
                    maxh = intensities.back();
                    mx = x;
                    my = y;
                }
            }

        cout << mx << " " << my << " " << maxh << endl;
    }

    Color heatmapColor(float intensity)
    {

        intensity = std::max(0.0f, std::min(1.0f, intensity));

        sf::Color blue(0, 0, 255), green(0, 255, 0), yellow(255, 255, 0), red(255, 0, 0);

        sf::Color color;
        if (intensity < 0.33)
        {
            float localIntensity = intensity / 0.33;
            color.r = blue.r + localIntensity * (green.r - blue.r);
            color.g = blue.g + localIntensity * (green.g - blue.g);
            color.b = blue.b + localIntensity * (green.b - blue.b);
        }
        else if (intensity < 0.66)
        {
            float localIntensity = (intensity - 0.33) / 0.33;
            color.r = green.r + localIntensity * (yellow.r - green.r);
            color.g = green.g + localIntensity * (yellow.g - green.g);
            color.b = green.b + localIntensity * (yellow.b - green.b);
        }
        else
        {
            float localIntensity = (intensity - 0.66) / 0.34;
            color.r = yellow.r + localIntensity * (red.r - yellow.r);
            color.g = yellow.g + localIntensity * (red.g - yellow.g);
            color.b = yellow.b + localIntensity * (red.b - yellow.b);
        }

        return color;
    }

    void draw()
    {
        for (int i = 0; i < points.size(); i++)
        {
            float intensity = (intensities[i] + 2) / 4;
        
            points[i].color = heatmapColor(intensity);
        }

        window.draw(&points[0], points.size(), sf::Points);
    }
};