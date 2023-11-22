
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
#include "PolygonInterior.hpp"
#include "TriangleMeshProcessor.hpp"
#include "ImageManager.hpp"
#include "NormalmapProcessor.hpp"
#include "Slider.hpp"
#include "ControlPointsUI.hpp"
#include "NormalmapButton.hpp"
using namespace std;
using namespace sf;

RenderWindow window;
Bitmap bitmap;

void myfunction_on()
{
    cout << "Button turned on!" << endl;
}

void myfunction_off()
{
    cout << "Button turned off!" << endl;
}

int main()
{
    window.create(VideoMode(W+300, H), "Bezier surface");
    window.setFramerateLimit(110);

    RectangleShape background(Vector2f(W+300, H));
    background.setFillColor(Color::White);

    FrameRateCalculator frameRateCalculator;
    Bezier bezier;
    PixelRenderer* renderer;

    LightSource lightSource;
    PhongReflectionProcessor prp(bezier, lightSource);
    FramePixelProcessor fpp(bezier, prp);
    TriangleMeshProcessor triangleMeshProcessor(bezier, prp);
    ControlPoints controlPoints(bezier, triangleMeshProcessor);

    // renderer = new GreenShadesPixelRenderer(bezier, lightSource);
    renderer = new PixelRenderer(bezier, lightSource, controlPoints);


    ImageManager::loadImage();
    triangleMeshProcessor.processFrame(true, true, 100, 100);
    Slider slider(250);
    Slider slider2(150);

    NormalmapButton normalmapButton(window, myfunction_on, myfunction_off, triangleMeshProcessor);
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
                
            slider.handleEvent(event);
            slider2.handleEvent(event);
            controlPoints.handleEvent(event);
            normalmapButton.handleEvent(event, window);
        }

        // frameRateCalculator.update();

        window.clear(Color::Black);
        // window.draw(background);
        lightSource.nextFrame();
        lightSource.adjustPosition();

        // // if(true) // here goes a condtition for changing control points
        // //     setHeights();

        triangleMeshProcessor.processFrame(false, false);

        slider.draw(window);
        slider2.draw(window);
        renderer->draw();
        
        slider2.handleEvent(event);
        normalmapButton.draw(window);

        window.display();
    }

    return 0;
}
