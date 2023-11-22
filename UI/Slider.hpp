#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.hpp"
#include "Bitmap.hpp"

using namespace std;
using namespace sf;

class Slider
{
public:
    RectangleShape background;
    RectangleShape handle;
    Font font;
    Text title;
    Text labelMin;
    Text labelMax;

    bool isDragging;

void computeValue()
{
    float relativeY = handle.getPosition().y - background.getPosition().y;
    // Reverse the calculation by subtracting from 1
    offsetThickness = 2 - ((relativeY / (background.getSize().y - handle.getSize().y)) * 4);
}


    Slider(int shift = 0)
    {
        if (!font.loadFromFile("./../UI/Arial.ttf"))
        {
            cout << "Failed to load font!" << endl;
        }

        background.setSize(Vector2f(30, 200));
        background.setPosition(M - 100 + shift, N / 6);
        background.setFillColor(Color::White);

        handle.setSize(Vector2f(30, 20));
        handle.setFillColor(Color::Blue);
        // Set the handle to the bottom of the slider by default.
        handle.setPosition(M - 100 + shift, N / 6 + background.getSize().y - handle.getSize().y);

        title.setFont(font);
        title.setString("Offset");
        title.setCharacterSize(20);
        title.setFillColor(Color::White);
        title.setPosition(M - 115 + shift, N / 6 - 30);

        labelMin.setFont(font);
        labelMin.setString("1"); // Changed back to 0.
        labelMin.setCharacterSize(15);
        labelMin.setFillColor(Color::White);
        labelMin.setPosition(M - 60 + shift, N / 6 + 180);

        labelMax.setFont(font);
        labelMax.setString("20");
        labelMax.setCharacterSize(15);
        labelMax.setFillColor(Color::White);
        labelMax.setPosition(M - 60 + shift, N / 6);

        isDragging = false;
        computeValue();
    }

    void handleEvent(const Event &event)
    {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            if (handle.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                isDragging = true;
            }
        }
        else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
        {
            isDragging = false;
        }
        else if (event.type == Event::MouseMoved && isDragging)
        {
            float newY = event.mouseMove.y - handle.getSize().y / 2;
            if (newY < background.getPosition().y)
            {
                newY = background.getPosition().y;
            }
            else if (newY > background.getPosition().y + background.getSize().y - handle.getSize().y)
            {
                newY = background.getPosition().y + background.getSize().y - handle.getSize().y;
            }
            handle.setPosition(handle.getPosition().x, newY);
            computeValue();
        }
    }

    void draw(RenderWindow &window)
    {
        window.draw(background);
        window.draw(handle);
        window.draw(title);
        window.draw(labelMin);
        window.draw(labelMax);
    }
};