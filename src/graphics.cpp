#include "graphics.h"
#include <iostream>
#include <cmath>  // Для математических функций

void Graphics::handleGraphics() {
    Graphics g(800, 600);
    g.run();
}

Graphics::Graphics(int width, int height) 
    : width(width), height(height), showMenu(true) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    window = SDL_CreateWindow("Graphics Menu", 
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width, height,
                            SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::renderMenu() {
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_Rect menu = {20, 20, 200, 150};
    SDL_RenderFillRect(renderer, &menu);
}

void Graphics::drawAxes() {
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderDrawLine(renderer, 0, height/2, width, height/2);
    SDL_RenderDrawLine(renderer, width/2, 0, width/2, height);
}

void Graphics::plotFunction(const std::function<double(double)>& func, double xMin, double xMax) {
    SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
    
    const double scaleY = height / 4.0;
    SDL_Point points[width];
    
    for (int i = 0; i < width; ++i) {
        double x = xMin + (xMax - xMin) * i / width;
        double y = func(x);
        int screenY = height/2 - static_cast<int>(y * scaleY);
        screenY = std::max(0, std::min(height-1, screenY));
        points[i] = {i, screenY};
    }
    
    SDL_RenderDrawLines(renderer, points, width);
}

void Graphics::run() {
    bool running = true;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                else if (event.key.keysym.sym == SDLK_m) {
                    showMenu = !showMenu;
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        drawAxes();
        plotFunction([](double x) { return std::sin(x); }, -10, 10);  // Исправленный вызов
        
        if (showMenu) {
            renderMenu();
        }
        
        SDL_RenderPresent(renderer);
    }
}