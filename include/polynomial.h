#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

const int MAX_DEGREE = 100;

struct Polynomial {
    double coeffs[MAX_DEGREE + 1];
    int degree;
};

void initZeroPolynomial(Polynomial* poly);
void removeLeadingZeros(Polynomial* poly);
Polynomial addPolynomials(const Polynomial* p1, const Polynomial* p2);
Polynomial subtractPolynomials(const Polynomial* p1, const Polynomial* p2);
Polynomial multiplyPolynomials(const Polynomial* p1, const Polynomial* p2);
Polynomial multiplyPolynomialByScalar(const Polynomial* p, double scalar);
int dividePolynomials(const Polynomial* dividend, const Polynomial* divisor,
                     Polynomial* quotient, Polynomial* remainder);
Polynomial derivative(const Polynomial* p);
void polynomialToString(const Polynomial* p, char* buffer, int bufferSize);
void parsePolynomial(const char* str, Polynomial* poly);
void handlePolynomialMenu(); 

#endif