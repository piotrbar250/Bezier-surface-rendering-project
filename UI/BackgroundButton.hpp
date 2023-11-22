#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

using namespace std;
using namespace sf;

// Define a type for the function pointer
using ButtonFunction = function<void()>;

class BackgroundButton
{
public:
    RectangleShape button;
    Text labelText;
    Font font;
    bool isOn;
    ButtonFunction onClickFunctionOn;
    ButtonFunction onClickFunctionOff;

    BackgroundButton(RenderWindow& window, ButtonFunction funcOn, ButtonFunction funcOff, const Vector2f& normalmapButtonPos)
    {
        if (!font.loadFromFile("./../UI/Arial.ttf"))
        {
            cout << "Failed to load font!" << endl;
        }

        // Set up the button shape
        button.setSize(Vector2f(100, 50));
        button.setFillColor(Color::Red);
        // Position to the left of the normalmap button
        button.setPosition(normalmapButtonPos.x - button.getSize().x - 10, normalmapButtonPos.y);

        // Set up the label
        labelText.setFont(font);
        labelText.setString("Background");
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
                    background = true;
                }
                else
                {
                    button.setFillColor(Color::Red);
                    onClickFunctionOff();
                    background = false;
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