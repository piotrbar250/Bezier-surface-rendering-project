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
    window.create(VideoMode(M, N), "Bezier surface");
    window.setFramerateLimit(60);
    FrameRateCalculator frameRateCalculator;
    Bezier bezier;
    PixelRenderer* renderer;
    FramePixelProcessor fpp(bezier);
    LightSource lightSource;

    renderer = new GreenShadesPixelRenderer(bezier, lightSource);
    // renderer = new PixelRenderer(bezier, lightSource);

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

        // if(true) // here goes a condtition for changing control points
        //     setHeights();
        fpp.calculateColors();
        
        renderer->draw();
        window.display();
    }

    return 0;
}

// #include <SFML/Graphics.hpp>
// #include <chrono>

// int main() {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Stable Rotating Light Source");
//     window.setFramerateLimit(60);

//     sf::CircleShape lightSource(5);
//     lightSource.setFillColor(sf::Color::Yellow);

//     const sf::Vector2f center(500, 500);
//     const float radius = 100.0f;
//     float angle = 0.0f;
    
//     auto lastTime = std::chrono::high_resolution_clock::now();

//     while (window.isOpen()) {
//         auto currentTime = std::chrono::high_resolution_clock::now();
//         float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
//         lastTime = currentTime;

//         // Event handling...

//         // Update light source position
//         angle += deltaTime * 1.0f; // speed is a constant determining rotation speed
//         if (angle > 2 * M_PI) {
//             angle -= 2 * M_PI; // Reset the angle after a full rotation
//         }

//         float x = center.x + radius * cos(angle);
//         float y = center.y + radius * sin(angle);
//         lightSource.setPosition(x, y);

//         window.clear();
//         window.draw(lightSource);
//         window.display();
//     }

//     return 0;
// }
