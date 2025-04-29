#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include <functional>
#include <cmath>  // Добавлен для sin()

class Graphics {
public:
    static void handleGraphics();
    
private:
    Graphics(int width, int height);
    ~Graphics();
    
    void run();
    void renderMenu();  // Объявлен метод
    void drawAxes();
    void plotFunction(const std::function<double(double)>& func, double xMin, double xMax);  // Полная сигнатура
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    bool showMenu;
};

#endif // GRAPHICS_H