// graphics.cpp
#include "graphics.h"
#include <iostream>
#include <cmath>
#include <iomanip>

// Прототипы функций для математических операций
double calculateIntegral(const std::function<double(double)>& func, double a, double b, int n = 1000);
double findRoot(const std::function<double(double)>& func, double a, double b, double epsilon = 1e-6);
std::vector<double> findExtremums(const std::function<double(double)>& func, double a, double b, int steps = 1000);

// Вспомогательные функции
void showMainMenu();
void showFunctionMenu();
void showMathMenu();
void handlePolynomialInput(std::vector<double>& coefficients);
void handlePowerFunctionInput(double& a, double& b, double& c);
void handleExponentialFunctionInput(double& a, double& b, double& c);
void handleLogarithmicFunctionInput(double& a, double& b, double& c);
void handleSinusoidalInput(double& a, double& b, double& c, double& d);
void handleCosineInput(double& a, double& b, double& c, double& d);

void Graphics::handleGraphics() {
    showMainMenu();
}

void showMainMenu() {
    while (true) {
        std::cout << "\n=== Главное меню ===" << std::endl;
        std::cout << "1. Построить график функции" << std::endl;
        std::cout << "2. Выполнить математические операции" << std::endl;
        std::cout << "0. Выход" << std::endl;
        
        int choice;
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        
        if (choice == 0) return;
        
        switch (choice) {
            case 1:
                showFunctionMenu();
                break;
            case 2:
                showMathMenu();
                break;
            default:
                std::cout << "Неверный выбор!" << std::endl;
        }
    }
}

void showFunctionMenu() {
    std::cout << "\n=== Выбор функции ===" << std::endl;
    std::cout << "1. Полином степени N" << std::endl;
    std::cout << "2. Степенная функция: a*x^b+c" << std::endl;
    std::cout << "3. Показательная функция: a*exp(b*x)+c" << std::endl;
    std::cout << "4. Логарифмическая функция: a*ln(b*x)+c" << std::endl;
    std::cout << "0. Назад" << std::endl;
    
    int choice;
    std::cout << "Выберите тип функции: ";
    std::cin >> choice;
    
    if (choice == 0) return;
    
    std::function<double(double)> func;
    double xMin, xMax;
    
    switch (choice) {
        case 1: {
            std::vector<double> coefficients;
            handlePolynomialInput(coefficients);
            func = [coefficients](double x) {
                double result = 0;
                for (int i = 0; i < coefficients.size(); ++i) {
                    result += coefficients[i] * std::pow(x, i);
                }
                return result;
            };
            xMin = -10;
            xMax = 10;
            break;
        }
        case 2: {
            double a, b, c;
            handlePowerFunctionInput(a, b, c);
            func = [a, b, c](double x) { return a * std::pow(x, b) + c; };
            xMin = 0.1;
            xMax = 10;
            break;
        }
        case 3: {
            double a, b, c;
            handleExponentialFunctionInput(a, b, c);
            func = [a, b, c](double x) { return a * std::exp(b * x) + c; };
            xMin = -5;
            xMax = 5;
            break;
        }
        case 4: {
            double a, b, c;
            handleLogarithmicFunctionInput(a, b, c);
            func = [a, b, c](double x) { return a * std::log(b * x) + c; };
            xMin = 0.1;
            xMax = 10;
            break;
        }
        default:
            std::cout << "Неверный выбор!" << std::endl;
            return;
    }
    
    // Создаем графическое окно
    Graphics g(800, 600);
    g.plotFunction(func, xMin, xMax);
    g.run();
}

void showMathMenu() {
    std::cout << "\n=== Математические операции ===" << std::endl;
    std::cout << "1. Вычислить определенный интеграл" << std::endl;
    std::cout << "2. Найти корень уравнения y=0" << std::endl;
    std::cout << "3. Найти экстремумы функции" << std::endl;
    std::cout << "0. Назад" << std::endl;
    
    int choice;
    std::cout << "Выберите операцию: ";
    std::cin >> choice;
    
    if (choice == 0) return;
    
    std::cout << "\n=== Выбор типа функции ===" << std::endl;
    std::cout << "1. Полином" << std::endl;
    std::cout << "2. Синусоида" << std::endl;
    std::cout << "3. Косинусоида" << std::endl;
    std::cout << "0. Назад" << std::endl;
    
    int funcType;
    std::cout << "Выберите тип функции: ";
    std::cin >> funcType;
    
    if (funcType == 0) return;
    
    std::function<double(double)> func;
    double a, b, c, d;
    double defaultXMin, defaultXMax;
    
    switch (funcType) {
        case 1: {
            std::vector<double> coefficients;
            handlePolynomialInput(coefficients);
            func = [coefficients](double x) {
                double result = 0;
                for (int i = 0; i < coefficients.size(); ++i) {
                    result += coefficients[i] * std::pow(x, i);
                }
                return result;
            };
            defaultXMin = -10;
            defaultXMax = 10;
            break;
        }
        case 2: {
            handleSinusoidalInput(a, b, c, d);
            func = [a, b, c, d](double x) { return a * std::sin(b * x + c) + d; };
            defaultXMin = -10;
            defaultXMax = 10;
            break;
        }
        case 3: {
            handleCosineInput(a, b, c, d);
            func = [a, b, c, d](double x) { return a * std::cos(b * x + c) + d; };
            defaultXMin = -10;
            defaultXMax = 10;
            break;
        }
        default:
            std::cout << "Неверный выбор!" << std::endl;
            return;
    }
    
    double xMin, xMax;
    std::cout << "Введите начало отрезка (по умолчанию " << defaultXMin << "): ";
    std::cin >> xMin;
    if (std::cin.fail()) {
        std::cin.clear();
        xMin = defaultXMin;
    }
    
    std::cout << "Введите конец отрезка (по умолчанию " << defaultXMax << "): ";
    std::cin >> xMax;
    if (std::cin.fail()) {
        std::cin.clear();
        xMax = defaultXMax;
    }
    
    switch (choice) {
        case 1: {
            double integral = calculateIntegral(func, xMin, xMax);
            std::cout << "Значение интеграла: " << std::setprecision(10) << integral << std::endl;
            break;
        }
        case 2: {
            double root = findRoot(func, xMin, xMax);
            std::cout << "Найденный корень: x = " << std::setprecision(10) << root << std::endl;
            break;
        }
        case 3: {
            auto extremums = findExtremums(func, xMin, xMax);
            if (extremums.empty()) {
                std::cout << "Экстремумы не найдены на заданном отрезке." << std::endl;
            } else {
                std::cout << "Найденные экстремумы:" << std::endl;
                for (double x : extremums) {
                    std::cout << "x = " << std::setprecision(10) << x << ", y = " << func(x) << std::endl;
                }
            }
            break;
        }
        default:
            std::cout << "Неверный выбор!" << std::endl;
    }
    
    // Показать график после вычислений
    Graphics g(800, 600);
    g.plotFunction(func, xMin, xMax);
    g.run();
}

void handlePolynomialInput(std::vector<double>& coefficients) {
    int degree;
    std::cout << "Введите степень полинома: ";
    std::cin >> degree;
    
    coefficients.resize(degree + 1);
    for (int i = 0; i <= degree; ++i) {
        std::cout << "Введите коэффициент a" << i << ": ";
        std::cin >> coefficients[i];
    }
}

void handlePowerFunctionInput(double& a, double& b, double& c) {
    std::cout << "Введите коэффициент a: ";
    std::cin >> a;
    std::cout << "Введите степень b: ";
    std::cin >> b;
    std::cout << "Введите константу c: ";
    std::cin >> c;
}

void handleExponentialFunctionInput(double& a, double& b, double& c) {
    std::cout << "Введите коэффициент a: ";
    std::cin >> a;
    std::cout << "Введите коэффициент b: ";
    std::cin >> b;
    std::cout << "Введите константу c: ";
    std::cin >> c;
}

void handleLogarithmicFunctionInput(double& a, double& b, double& c) {
    std::cout << "Введите коэффициент a: ";
    std::cin >> a;
    std::cout << "Введите коэффициент b: ";
    std::cin >> b;
    std::cout << "Введите константу c: ";
    std::cin >> c;
}

void handleSinusoidalInput(double& a, double& b, double& c, double& d) {
    std::cout << "Введите амплитуду a: ";
    std::cin >> a;
    std::cout << "Введите частоту b: ";
    std::cin >> b;
    std::cout << "Введите фазу c: ";
    std::cin >> c;
    std::cout << "Введите смещение d: ";
    std::cin >> d;
}

void handleCosineInput(double& a, double& b, double& c, double& d) {
    std::cout << "Введите амплитуду a: ";
    std::cin >> a;
    std::cout << "Введите частоту b: ";
    std::cin >> b;
    std::cout << "Введите фазу c: ";
    std::cin >> c;
    std::cout << "Введите смещение d: ";
    std::cin >> d;
}

double calculateIntegral(const std::function<double(double)>& func, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));
    
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }
    
    return sum * h;
}

double findRoot(const std::function<double(double)>& func, double a, double b, double epsilon) {
    if (func(a) * func(b) >= 0) {
        std::cerr << "На границах интервала функция должна иметь разные знаки!" << std::endl;
        return NAN;
    }
    
    double c = a;
    while ((b - a) >= epsilon) {
        c = (a + b) / 2;
        if (func(c) == 0.0) {
            break;
        } else if (func(c) * func(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    
    return c;
}

std::vector<double> findExtremums(const std::function<double(double)>& func, double a, double b, int steps) {
    std::vector<double> extremums;
    double h = (b - a) / steps;
    
    // Простая численная производная
    auto derivative = [&func, h](double x) {
        return (func(x + h) - func(x - h)) / (2 * h);
    };
    
    // Ищем точки, где производная меняет знак
    for (int i = 1; i < steps; ++i) {
        double x1 = a + (i - 1) * h;
        double x2 = a + i * h;
        double x3 = a + (i + 1) * h;
        
        double d1 = derivative(x1);
        double d2 = derivative(x2);
        double d3 = derivative(x3);
        
        // Проверяем смену знака производной
        if ((d1 * d2 < 0) || (d2 * d3 < 0)) {
            // Уточняем положение экстремума методом Ньютона
            double x = x2;
            for (int iter = 0; iter < 10; ++iter) {
                double dx = derivative(x);
                if (std::abs(dx) < 1e-10) break;
                double d2x = (derivative(x + h) - derivative(x - h)) / (2 * h);
                if (std::abs(d2x) < 1e-10) break;
                x = x - dx / d2x;
            }
            
            // Проверяем, что точка внутри интервала и не дублируется
            if (x >= a && x <= b && 
                (extremums.empty() || std::abs(x - extremums.back()) > h)) {
                extremums.push_back(x);
            }
        }
    }
    
    return extremums;
}

Graphics::Graphics(int width, int height) 
    : width(width), height(height), currentFunc([](double){ return 0; }), currentXMin(0), currentXMax(0) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    window = SDL_CreateWindow("График функции", 
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width, height,
                            SDL_WINDOW_SHOWN);
    
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::drawAxes() {
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderDrawLine(renderer, 0, height/2, width, height/2);  // Ось X
    SDL_RenderDrawLine(renderer, width/2, 0, width/2, height);   // Ось Y
    
    // Подписи осей
    // Здесь можно добавить код для отображения текста с помощью SDL_ttf
}

void Graphics::plotFunction(const std::function<double(double)>& func, double xMin, double xMax) {
    currentFunc = func;
    currentXMin = xMin;
    currentXMax = xMax;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    drawAxes();
    
    SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
    
    const double scaleY = height / (2.0 * (std::abs(xMax - xMin) > 0.1 ? std::max(std::abs(func(xMin)), std::abs(func(xMax))) * 2.5 : 5.0));
    const double scaleX = width / (xMax - xMin);
    
    // Рисуем график по точкам
    for (int i = 0; i < width; ++i) {
        double x = xMin + (xMax - xMin) * i / width;
        double y = func(x);
        int screenX = static_cast<int>((x - xMin) * scaleX);
        int screenY = height/2 - static_cast<int>(y * scaleY);
        screenY = std::max(0, std::min(height-1, screenY));
        
        SDL_RenderDrawPoint(renderer, screenX, screenY);
    }
    
    SDL_RenderPresent(renderer);
}

void Graphics::run() {
    bool running = true;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }
        
        SDL_Delay(16);
    }
}