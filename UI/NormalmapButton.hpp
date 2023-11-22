#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "TriangleMeshProcessor.hpp"
using namespace std;
using namespace sf;

// Define a type for the function pointer
using ButtonFunction = function<void()>;

class NormalmapButton
{
public:
    TriangleMeshProcessor& triangleMeshProcessor;
    RectangleShape button;
    Text labelText;
    Font font;
    bool isOn;
    ButtonFunction onClickFunctionOn;
    ButtonFunction onClickFunctionOff;

    NormalmapButton(RenderWindow& window, ButtonFunction funcOn, ButtonFunction funcOff, TriangleMeshProcessor& triangleMeshProcessor) : triangleMeshProcessor(triangleMeshProcessor)
    {
        if (!font.loadFromFile("./../UI/Arial.ttf"))
        {
            cout << "Failed to load font!" << endl;
        }

        // Set up the button shape
        button.setSize(Vector2f(100, 50));
        button.setFillColor(Color::Red);
        button.setPosition(window.getSize().x - button.getSize().x - 10, window.getSize().y - button.getSize().y - 10);

        // Set up the label
        labelText.setFont(font);
        labelText.setString("Normalmap");
        labelText.setCharacterSize(20);
        labelText.setFillColor(Color::White);
        labelText.setPosition(button.getPosition().x, button.getPosition().y - 30);

        // Initialize state and set the functions to be called on click
        isOn = false;
        onClickFunctionOn = funcOn;
        onClickFunctionOff = funcOff;
    }

    void handleEvent(const Event &event, RenderWindow& window)
    {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (button.getGlobalBounds().contains(mousePos))
            {
                // Toggle the state
                isOn = !isOn;

                // Change color and call the respective function based on the state
                if (isOn)
                {
                    button.setFillColor(Color::Green);
                    onClickFunctionOn();
                    triangleMeshProcessor.launchNormalmap();
                }
                else
                {
                    button.setFillColor(Color::Red);
                    onClickFunctionOff();
                    triangleMeshProcessor.hideNormalmap();
                }
            }
        }
    }

    void draw(RenderWindow &window)
    {
        window.draw(button);
        window.draw(labelText);
    }
};