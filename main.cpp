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
    window.create(VideoMode(W, H), "Bezier surface");
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

// #include <SFML/Graphics.hpp>

// int main()
// {
//     // Create a window
//     const int W = 1000;
//     const int H = 600;
//     sf::RenderWindow window(sf::VideoMode(W, H), "Single Pixel Example");

//     // Create a pixel
//     sf::VertexArray pixel(sf::Points, 1);
//     pixel[0].position = sf::Vector2f(500, 100);
//     pixel[0].color = sf::Color::White;

//     // Run the program as long as the window is open
//     while (window.isOpen())
//     {
//         // Check all the window's events that were triggered since the last iteration of the loop
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             // "Close requested" event: we close the window
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // Clear the window with black color
//         window.clear(sf::Color::Black);

//         // Draw the pixel
//         window.draw(pixel);

//         // Update the window
//         window.display();
//     }

//     return 0;
// }
// #include <SFML/Graphics.hpp>

// int main()
// {
//     // Create the main window
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window - Multiple Triangles");

//     // Define a vertex array to hold multiple triangles
//     sf::VertexArray triangles(sf::Triangles, 9); // 3 vertices per triangle * 3 triangles

//     // First triangle
//     triangles[0].position = sf::Vector2f(100, 100);
//     triangles[0].color = sf::Color::Red;

//     triangles[1].position = sf::Vector2f(200, 100);
//     triangles[1].color = sf::Color::Green;

//     triangles[2].position = sf::Vector2f(150, 200);
//     triangles[2].color = sf::Color::Blue;

//     // Second triangle
//     triangles[3].position = sf::Vector2f(300, 100);
//     triangles[3].color = sf::Color::Yellow;

//     triangles[4].position = sf::Vector2f(400, 100);
//     triangles[4].color = sf::Color::Magenta;

//     triangles[5].position = sf::Vector2f(350, 200);
//     triangles[5].color = sf::Color::Cyan;

//     // Third triangle
//     triangles[6].position = sf::Vector2f(500, 100);
//     triangles[6].color = sf::Color::White;

//     triangles[7].position = sf::Vector2f(600, 100);
//     triangles[7].color = sf::Color::Black;

//     triangles[8].position = sf::Vector2f(550, 200);
//     triangles[8].color = sf::Color::Blue;

//     // Start the game loop
//     while (window.isOpen())
//     {
//         // Process events
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // Clear screen
//         window.clear();

//         // Draw the triangles
//         window.draw(triangles);

//         // Update the window
//         window.display();
//     }

//     return 0;
// }