#include "fractions.h"
#include <iostream>
#include <numeric>
#include <limits>

namespace Fractions {

using std::cout;
using std::cin;
using std::endl;

void Fraction::simplify() {
    int common_divisor = std::gcd(numerator, denominator);
    numerator /= common_divisor;
    denominator /= common_divisor;
    
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

Fraction add(const Fraction& f1, const Fraction& f2) {
    int new_num = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    int new_den = f1.denominator * f2.denominator;
    return Fraction(new_num, new_den);
}

Fraction subtract(const Fraction& f1, const Fraction& f2) {
    int new_num = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    int new_den = f1.denominator * f2.denominator;
    return Fraction(new_num, new_den);
}

Fraction multiply(const Fraction& f1, const Fraction& f2) {
    return Fraction(f1.numerator * f2.numerator, 
                   f1.denominator * f2.denominator);
}

Fraction divide(const Fraction& f1, const Fraction& f2) {
    if (f2.numerator == 0) {
        throw std::invalid_argument("Нельзя делить на 0");
    }
    return Fraction(f1.numerator * f2.denominator, 
                   f1.denominator * f2.numerator);
}

int compare(const Fraction& f1, const Fraction& f2) {
    int left = f1.numerator * f2.denominator;
    int right = f2.numerator * f1.denominator;
    
    if (left < right) return -1;
    if (left > right) return 1;
    return 0;
}

double toDecimal(const Fraction& f) {
    return static_cast<double>(f.numerator) / f.denominator;
}

void printFraction(const Fraction& f) {
    cout << f.numerator;
    if (f.denominator != 1) {
        cout << "/" << f.denominator;
    }
}

void handleFractionsMenu() {
    Fraction f1, f2;
    int choice;
    
    do {
        cout << "\nМеню операций с дробями:\n"
             << "1. Ввести первую дробь\n"
             << "2. Ввести вторую дробь\n"
             << "3. Сложение\n"
             << "4. Вычитание\n"
             << "5. Умножение\n"
             << "6. Деление\n"
             << "7. Сравнение\n"
             << "8. Десятичное представление\n"
             << "0. Назад\n"
             << "Выбор: ";
        
        cin >> choice;
        
        try {
            switch (choice) {
                case 1: {
                    cout << "Введите числитель и знаменатель (через пробел): ";
                    cin >> f1.numerator >> f1.denominator;
                    f1.simplify();
                    cout << "Дробь 1: ";
                    printFraction(f1);
                    cout << endl;
                    break;
                }
                case 2: {
                    cout << "Введите числитель и знаменатель (через пробел): ";
                    cin >> f2.numerator >> f2.denominator;
                    f2.simplify();
                    cout << "Дробь 2: ";
                    printFraction(f2);
                    cout << endl;
                    break;
                }
                case 3: {
                    Fraction result = add(f1, f2);
                    printFraction(f1); cout << " + "; printFraction(f2); 
                    cout << " = "; printFraction(result); cout << endl;
                    break;
                }
                case 4: {
                    Fraction result = subtract(f1, f2);
                    printFraction(f1); cout << " - "; printFraction(f2); 
                    cout << " = "; printFraction(result); cout << endl;
                    break;
                }
                case 5: {
                    Fraction result = multiply(f1, f2);
                    printFraction(f1); cout << " * "; printFraction(f2); 
                    cout << " = "; printFraction(result); cout << endl;
                    break;
                }
                case 6: {
                    Fraction result = divide(f1, f2);
                    printFraction(f1); cout << " / "; printFraction(f2); 
                    cout << " = "; printFraction(result); cout << endl;
                    break;
                }
                case 7: {
                    int cmp = compare(f1, f2);
                    printFraction(f1); 
                    cout << (cmp < 0 ? " < " : cmp > 0 ? " > " : " == ");
                    printFraction(f2); cout << endl;
                    break;
                }
                case 8: {
                    cout << "Десятичное представление:\n";
                    cout << "Дробь 1: "; printFraction(f1); 
                    cout << " = " << toDecimal(f1) << endl;
                    cout << "Дробь 2: "; printFraction(f2); 
                    cout << " = " << toDecimal(f2) << endl;
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch (const std::exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);
}

}