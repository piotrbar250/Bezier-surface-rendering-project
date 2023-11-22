#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.hpp"
#include "Bitmap.hpp"
#include "PhongReflectionProcessor.hpp"
#include "TriangleMeshProcessor.hpp"
#include "LightSource.hpp"

using namespace std;
using namespace sf;

class BezierSlider
{
public:
    LightSource& lightSource;
    TriangleMeshProcessor& triangleMeshProcessor;
    PhongReflectionProcessor& prp;
    RectangleShape background;
    RectangleShape handle;
    Font font;
    Text title;
    Text labelMin;
    Text labelMax;

    bool isDragging;
    function<void()> onHandleMoved;

    void adjustBezierValue()
    {
        float relativeY = handle.getPosition().y - background.getPosition().y;
        // Reverse the calculation by subtracting from 1
        offsetThickness = 2 - ((relativeY / (background.getSize().y - handle.getSize().y)) * 4);
        cout << "offsetThickness: " << offsetThickness << endl;
    }

    void adjustKd()
    {

        float relativeY = handle.getPosition().y - background.getPosition().y;
    // Invert the calculation to ensure the value increases as the handle moves up
        float kd = 1.0f - (relativeY / (background.getSize().y - handle.getSize().y));
        cout << "Kd value: " << kd << endl;
        prp.setKd(kd);
    }

    void adjustKs()
    {

        float relativeY = handle.getPosition().y - background.getPosition().y;
    // Invert the calculation to ensure the value increases as the handle moves up
        float ks = 1.0f - (relativeY / (background.getSize().y - handle.getSize().y));
        cout << "Ks value: " << ks << endl;
        prp.setKs(ks);
    }

    void adjustMesh()
    {
static const vector<int> discreteValues = {2, 4, 5, 8, 10, 16, 20, 25, 32, 40, 50, 80, 100};
    float relativeY = handle.getPosition().y - background.getPosition().y;
    float ratio = 1.0f - (relativeY / (background.getSize().y - handle.getSize().y)); // Inverted ratio

    // Find the closest discrete value
    size_t index = static_cast<size_t>(ratio * discreteValues.size());
    if (index >= discreteValues.size()) index = discreteValues.size() - 1;

    int selectedValue = discreteValues[index];
    cout << "Mesh value: " << selectedValue << endl;
        triangleMeshProcessor.processFrame(false, true, selectedValue, selectedValue);
    }

    void adjustZ()
{
    float relativeY = handle.getPosition().y - background.getPosition().y;
    float ratio = 1.0f - (relativeY / (background.getSize().y - handle.getSize().y));
    
    // Map the ratio to the range 0.01 to 2
    float zValue = 0.01f + (1.99f * ratio);
    cout << "Z value: " << zValue << endl;
    lightSource.setZ(zValue);
}

void adjustM()
{
    float relativeY = handle.getPosition().y - background.getPosition().y;
    float ratio = 1.0f - (relativeY / (background.getSize().y - handle.getSize().y));

    // Map the ratio to the range 1 to 100
    int mValue = static_cast<int>(1 + 99 * ratio);
    cout << "M value: " << mValue << endl;
    prp.setM(mValue); // Assuming there's a method setM in PhongReflectionProcessor
}


    BezierSlider(PhongReflectionProcessor & prp, TriangleMeshProcessor& triangleMeshProcessor, LightSource& lightSource, function<void()> func, int shift = 0, int shiftV = 0) : prp(prp), onHandleMoved(func), triangleMeshProcessor(triangleMeshProcessor), lightSource(lightSource)
    {
        if (!font.loadFromFile("./../UI/Arial.ttf"))
        {
            cout << "Failed to load font!" << endl;
        }

        background.setSize(Vector2f(30, 200));
        background.setPosition(M - 100 + shift, N / 6 + shiftV);
        background.setFillColor(Color::White);

        handle.setSize(Vector2f(30, 20));
        handle.setFillColor(Color::Blue);
        // Set the handle to the bottom of the slider by default.
        handle.setPosition(M - 100 + shift, N / 6 + background.getSize().y - handle.getSize().y + shiftV);

        title.setFont(font);
        title.setString("Offset");
        title.setCharacterSize(20);
        title.setFillColor(Color::White);
        title.setPosition(M - 115 + shift, N / 6 - 30 + shiftV);

        labelMin.setFont(font);
        labelMin.setString("1"); // Changed back to 0.
        labelMin.setCharacterSize(15);
        labelMin.setFillColor(Color::White);
        labelMin.setPosition(M - 60 + shift, N / 6 + 180 + shiftV);

        labelMax.setFont(font);
        labelMax.setString("20");
        labelMax.setCharacterSize(15);
        labelMax.setFillColor(Color::White);
        labelMax.setPosition(M - 60 + shift, N / 6 + shiftV);

        isDragging = false;
        adjustBezierValue();
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
            onHandleMoved();
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

/*
I have two sliders

This one works fine
    BezierSlider bezierSlider(prp, [&](){bezierSlider.adjustBezierValue();}, 150, -80);
    
This one doesn't
    BezierSlider kdSlider(prp, [&](){bezierSlider.adjustKd();}, 250, -80);

*/
