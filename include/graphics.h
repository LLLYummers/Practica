#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include <functional>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

class Graphics {
public:
    static void handleGraphics();

    Graphics(int width, int height);
    ~Graphics();

    void run();
    void plotFunction(const std::function<double(double)>& func, double xMin, double xMax);
    
private:
    void drawAxes();
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    std::function<double(double)> currentFunc;
    double currentXMin;
    double currentXMax;
};

#endif