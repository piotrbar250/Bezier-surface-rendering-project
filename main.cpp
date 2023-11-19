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
#include "FrameRateCalculator.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

RenderWindow window;
Bitmap bitmap;

int main()
{
    // Bezier bez;
    // cout << bez.B(0, 2, 0.75) << endl;
    // return 0;
    window.create(VideoMode(W, H), "Bezier surface");
    window.setFramerateLimit(60);
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

        lightSource.nextFrame();
        lightSource.adjustPosition();

        // if(true) // here goes a condtition for changing control points
        //     setHeights();
        fpp.calculateColors();
        
        renderer->draw();
        window.display();
    }

    return 0;
}
