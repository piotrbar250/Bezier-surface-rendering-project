#ifndef FRAME_RATE_CALCULATOR_HPP
#define FRAME_RATE_CALCULATOR_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class FrameRateCalculator {
public:
    FrameRateCalculator() : frameTimes(0.0f), frameCount(0) {}

    void update() {
        frameTimes += clock.restart().asSeconds();
        frameCount++;

        if (frameCount == frameInterval) {
            float averageFrameTime = frameTimes / frameCount;
            float fps = 1.0f / averageFrameTime;
            std::cout << "Average FPS: " << fps << std::endl;

            reset();
        }
    }

private:
    void reset() {
        frameTimes = 0.0f;
        frameCount = 0;
    }

    sf::Clock clock;
    float frameTimes;
    int frameCount;
    const int frameInterval = 50;
};

#endif // FRAME_RATE_CALCULATOR_HPP
