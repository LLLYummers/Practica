#ifndef FRACTIONS_H
#define FRACTIONS_H

#include <iostream>
#include <numeric>
#include <stdexcept>

namespace Fractions {

struct Fraction {
    int numerator;
    int denominator;
    
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        simplify();
    }
    
    void simplify();
};

Fraction add(const Fraction& f1, const Fraction& f2);
Fraction subtract(const Fraction& f1, const Fraction& f2);
Fraction multiply(const Fraction& f1, const Fraction& f2);
Fraction divide(const Fraction& f1, const Fraction& f2);

int compare(const Fraction& f1, const Fraction& f2);
double toDecimal(const Fraction& f);

void printFraction(const Fraction& f);
void handleFractionsMenu();

} // namespace Fractions

#endif