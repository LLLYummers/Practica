#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <iostream>
#include "statistics.h"
#include "matrix.h"
#include "fractions.h"
#include "polynomial.h"
#include "combinatorics.h"
#include "graphics.h"
#include "SDL.h"

// Функция для включения поддержки ANSI в Винде
#ifdef _WIN32
void enableANSIConsole() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
void enableANSIConsole() {
    // Do nothing on non-Windows platforms
}
#endif

// Ниже функция и прочее для реализации красивого лого :3
const std::vector<std::string> rainbowColors = {
    "\033[38;5;196m", // Red
    "\033[38;5;208m", // Orange
    "\033[38;5;226m", // Yellow
    "\033[38;5;46m",  // Green
    "\033[38;5;21m",  // Blue
    "\033[38;5;93m",  // Indigo
    "\033[38;5;201m"  // Violet
};

const std::string resetColor = "\033[0m";

void printPracticaLogo() {
    const std::vector<std::string> logoLines = {
        "      ____                  __  _                    ",
        "     / __ \\_________ ______/ /_(_)________ _         ",
        "    / /_/ / ___/ __ `/ ___/ __/ / ___/ __ `/         ",
        "   / ____/ /  / /_/ / /__/ /_/ / /__/ /_/ /          ",
        "  /_/ __/_/__ \\__,_/\\___/\\__/_/\\___/\\__,_/           ",
        "     /  |/  /___ _(_)___     /  |/  /__  ____  __  __",
        "    / /|_/ / __ `/ / __ \\   / /|_/ / _ \\/ __ \\/ / / /",
        "   / /  / / /_/ / / / / /  / /  / /  __/ / / / /_/ / ",
        "  /_/  /_/\\__,_/_/_/ /_/  /_/  /_/\\___/_/ /_/\\__,_/  ",
        "                                                     "
    };

    for (size_t i = 0; i < logoLines.size(); ++i) {
        std::cout << rainbowColors[i % rainbowColors.size()] << logoLines[i] << resetColor << std::endl;
    }
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) {
#else
int main(int argc, char* argv[]) {
#endif
    
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    enableANSIConsole();

    // Перенаправление стандартного ввода/вывода для работы с Виндузятной консолью 
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
#endif

    int choice;
    do {
        
        printPracticaLogo();
        std::cout << "1. Калькулятор Формул Комбинаторики\n";
        std::cout << "2. Калькулятор многочленов\n";
        std::cout << "3. Матричный калькулятор\n";
        std::cout << "4. Тер.вер и мат. статистика\n";
        std::cout << "5. Калькулятор обыкновенных дробей\n";
        std::cout << "6. Работа с функциями\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите раздел: ";

        std::cin >> choice;

        switch (choice) {
            case 1:
            // Калькулятор Формул Комбинаторики 
                Combinatorics::handleCombinatorics();
                break;
            case 2:
            // Калькулятор многочленов
                handlePolynomialMenu();
                break;
            case 3:
            // Матричный калькулятор 
                MenuMatrix();
                break;
            
            case 4:
            // Тер.вер и мат. статистика
                Fractions::handleFractionsMenu();
                break;
            case 5:
            // Калькулятор обыкновенных дробей
                Statistics::handleStatisticsMenu();
                break;
            case 6:
            // Работа с функциями
                Graphics::handleGraphics();
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}