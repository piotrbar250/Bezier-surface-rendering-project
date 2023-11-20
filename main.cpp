// const int N = 720, M = 1152;
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Renderer/HeatMapPixelRenderer.hpp"
#include "Renderer/PixelRenderer.hpp"
#include "GreenShadesPixelRenderer.hpp"
#include "FramePixelProcessor.hpp"
#include "Bitmap.hpp"
#include "FrameRateCalculator.hpp"
#include <iostream>
#include <string>
#include "PolygonFilling.hpp"

using namespace std;
using namespace sf;

RenderWindow window;
Bitmap bitmap;

int main()
{
    window.create(VideoMode(W, H), "Bezier surface");
    window.setFramerateLimit(70);

    RectangleShape background(Vector2f(W+300, H));
    background.setFillColor(Color::White);

    FrameRateCalculator frameRateCalculator;
    Bezier bezier;
    PixelRenderer* renderer;
    
    LightSource lightSource;
    PhongReflectionProcessor prp(bezier, lightSource);
    FramePixelProcessor fpp(bezier, prp);

    // renderer = new GreenShadesPixelRenderer(bezier, lightSource);
    renderer = new PixelRenderer(bezier, lightSource);

    fpp.calculateHeights();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        frameRateCalculator.update();
        
        window.clear(Color::Black);
        // window.draw(background);

        lightSource.nextFrame();
        lightSource.adjustPosition();

        // // if(true) // here goes a condtition for changing control points
        // //     setHeights();
        fpp.calculateColors();
        
        renderer->draw();

        // PolygonFilling::drawPolygon();

        window.display();
        // return 0;
    }

    return 0;
}

