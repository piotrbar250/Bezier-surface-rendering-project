
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
#include "BezierSlider.hpp"
#include "ControlPointsUI.hpp"
#include "NormalmapButton.hpp"
#include "BackgroundButton.hpp"

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
    window.create(VideoMode(W+400, H), "Bezier surface");
    window.setFramerateLimit(110);


    sf::View normalView(sf::FloatRect(0, 0, W+400, H));
    sf::View shrunkView(sf::FloatRect(0, 0, W, H)); // smaller width
    bool isShrunk = false;

    RectangleShape background(Vector2f(W+400, H));
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
    // BezierSlider slider(250);
    BezierSlider bezierSlider(prp, triangleMeshProcessor, [&](){bezierSlider.adjustBezierValue();}, 150, -80);
    
    BezierSlider meshSlider(prp, triangleMeshProcessor, [&](){ meshSlider.adjustMesh(); }, 250, -80);
    
    BezierSlider zSlider(prp, triangleMeshProcessor, [&](){ zSlider.adjustMesh(); }, 350, -80);

    BezierSlider kdSlider(prp, triangleMeshProcessor, [&](){kdSlider.adjustKd();}, 150, 180);

    BezierSlider ksSlider(prp, triangleMeshProcessor, [&](){ksSlider.adjustKs();}, 250, 180);
    
    BezierSlider mSlider(prp, triangleMeshProcessor, [&](){mSlider.adjustKs();}, 350, 180);


    NormalmapButton normalmapButton(window, myfunction_on, myfunction_off, triangleMeshProcessor);

    Vector2f normalmapButtonPos(window.getSize().x - 100 - 30, window.getSize().y - 50 - 10);

    BackgroundButton backgroundButton(window, myfunction_on, myfunction_off, normalmapButtonPos);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            
            bezierSlider.handleEvent(event);
            meshSlider.handleEvent(event);
            kdSlider.handleEvent(event);
            ksSlider.handleEvent(event);
            
            controlPoints.handleEvent(event);
            normalmapButton.handleEvent(event, window);
            backgroundButton.handleEvent(event, window);

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::H) {
                    if (!isShrunk) {
                        window.setView(shrunkView); // Set the cropped view
                        window.setSize(sf::Vector2u(W, H)); // Resize window
                        isShrunk = true;
                    } else {
                        window.setView(normalView); // Set the normal view
                        window.setSize(sf::Vector2u(W+300, H)); // Resize window back to original size
                        isShrunk = false;
                    }
                }
            }
            
        }

        // frameRateCalculator.update();

        window.clear(Color::Black);
        // window.draw(background);
        lightSource.nextFrame();
        lightSource.adjustPosition();

        // // if(true) // here goes a condtition for changing control points
        // //     setHeights();

        triangleMeshProcessor.processFrame(false, false);

        // slider.draw(window);
        bezierSlider.draw(window);
        // meshSlider.draw(window);
        meshSlider.draw(window);
        kdSlider.draw(window);
        ksSlider.draw(window);
        zSlider.draw(window);
        mSlider.draw(window);
        renderer->draw();
        
        // slider2.handleEvent(event);
        normalmapButton.draw(window);
        backgroundButton.draw(window);
        window.display();
    }

    return 0;
}
