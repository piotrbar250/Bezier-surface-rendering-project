// const int N = 720, M = 1152;
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "HeatMapPixelRenderer.hpp"
#include <iostream>

using namespace std;
using namespace sf;

RenderWindow window;

int main()
{
    window.create(VideoMode(M, N), "Bezier surface");

    Bezier bezier;
    HeatMapPixelRenderer renderer(bezier);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);
        renderer.draw();
        window.display();
    }

    return 0;
}
