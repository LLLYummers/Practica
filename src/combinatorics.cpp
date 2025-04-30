#include "combinatorics.h"
#include <iostream>
#include <cmath>

using namespace std;

long long Combinatorics::factorial(int n) {
    if (n < 0) return 0;
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

long long Combinatorics::arrangementsWithoutRepetition(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return factorial(n) / factorial(n - k);
}

long long Combinatorics::arrangementsWithRepetition(int n, int k) {
    if (n < 0 || k < 0) return 0;
    long long result = 1;
    for (int i = 0; i < k; ++i) {
        result *= n;
    }
    return result;
}

long long Combinatorics::combinationsWithoutRepetition(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    long long result = 1;
    for (int i = 1; i <= k; ++i) {
        result *= (n - k + i);
        result /= i;
    }
    return result;
}

long long Combinatorics::combinationsWithRepetition(int n, int k) {
    return combinationsWithoutRepetition(n + k - 1, k);
}

long long Combinatorics::permutations(int n) {
    return factorial(n);
}

void Combinatorics::handleCombinatorics() {
    cout << "Калькулятор формул комбинаторики\n";

    int choice;
    do {
        cout << "\nМеню калькулятора комбинаторики:\n";
        cout << "1. Размещения с повторением\n";
        cout << "2. Размещения без повторений\n";
        cout << "3. Сочетания с повторением\n";
        cout << "4. Сочетания без повторений\n";
        cout << "5. Перестановки\n";
        cout << "0. Выход\n";
        cout << "Выберите операцию: ";
        cin >> choice;
        int n, k;

        if ((choice >= 1) && (choice <= 4)) { 
            cout << "Введите n и k (через пробел): "; 
            cin >> n >> k; 
        } else if (choice == 5) { 
            cout << "Введите n: "; 
            cin >> n; 
        }

        switch (choice) {
            case 1:
                cout << "A(" << n << ", " << k << ") с повторением = " 
                     << arrangementsWithRepetition(n, k) << endl; 
                break;
            case 2:
                cout << "A(" << n << ", " << k << ") без повторений = " 
                     << arrangementsWithoutRepetition(n, k) << endl; 
                break;
            case 3:
                cout << "C(" << n << ", " << k << ") с повторением = " 
                     << combinationsWithRepetition(n, k) << endl; 
                break;
            case 4:
                cout << "C(" << n << ", " << k << ") без повторений = " 
                     << combinationsWithoutRepetition(n, k) << endl; 
                break;
            case 5:
                cout << "P(" << n << ") = " << permutations(n) << endl; 
                break;
            case 0:
                cout << "Выход из калькулятора комбинаторики.\n"; 
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n"; 
                break;
        }
    } while (choice != 0);
}