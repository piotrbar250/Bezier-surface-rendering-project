// const int N = 720, M = 1152;
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "HeatMapPixelRenderer.hpp"
#include "PixelRenderer.hpp"
#include "GreenShadesPixelRenderer.hpp"
#include "FramePixelProcessor.hpp"
#include "Bitmap.hpp"
#include <iostream>

using namespace std;
using namespace sf;

RenderWindow window;
Bitmap bitmap;

int main()
{
    window.create(VideoMode(M, N), "Bezier surface");

    Bezier bezier;
    PixelRenderer* renderer;
    FramePixelProcessor fpp(bezier);

    // renderer = new GreenShadesPixelRenderer(bezier);
    renderer = new PixelRenderer(bezier);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);

        if(true) // here goes a condtition for changing control points
            fpp.calculateHeights();
        fpp.calculateColors();
        
        renderer->draw();
        window.display();
    }

    return 0;
}
