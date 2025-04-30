#include <iostream>
#include <cmath>
#include <cstdio>
#include "polynomial.h"

using namespace std;

void initZeroPolynomial(Polynomial* poly) {
    (*poly).degree = 0;
    for (int i = 0; i <= MAX_DEGREE; ++i) {
        (*poly).coeffs[i] = 0.0;
    }
}

void removeLeadingZeros(Polynomial* poly) {
    while ((*poly).degree > 0 && (*poly).coeffs[0] == 0.0) {
        for (int i = 0; i < (*poly).degree; ++i) {
            (*poly).coeffs[i] = (*poly).coeffs[i + 1];
        }
        (*poly).degree--;
    }
}

Polynomial addPolynomials(const Polynomial* p1, const Polynomial* p2) {
    Polynomial result;
    initZeroPolynomial(&result);

    int maxDegree = ((*p1).degree > (*p2).degree) ? (*p1).degree : (*p2).degree;
    result.degree = maxDegree;

    for (int i = 0; i <= maxDegree; ++i) {
        double c1 = (i <= (*p1).degree) ? (*p1).coeffs[(*p1).degree - i] : 0.0;
        double c2 = (i <= (*p2).degree) ? (*p2).coeffs[(*p2).degree - i] : 0.0;
        result.coeffs[maxDegree - i] = c1 + c2;
    }

    removeLeadingZeros(&result);
    return result;
}

Polynomial subtractPolynomials(const Polynomial* p1, const Polynomial* p2) {
    Polynomial result;
    initZeroPolynomial(&result);

    int maxDegree = ((*p1).degree > (*p2).degree) ? (*p1).degree : (*p2).degree;
    result.degree = maxDegree;

    for (int i = 0; i <= maxDegree; ++i) {
        double c1 = (i <= (*p1).degree) ? (*p1).coeffs[(*p1).degree - i] : 0.0;
        double c2 = (i <= (*p2).degree) ? (*p2).coeffs[(*p2).degree - i] : 0.0;
        result.coeffs[maxDegree - i] = c1 - c2;
    }

    removeLeadingZeros(&result);
    return result;
}

Polynomial multiplyPolynomials(const Polynomial* p1, const Polynomial* p2) {
    Polynomial result;
    initZeroPolynomial(&result);

    result.degree = (*p1).degree + (*p2).degree;

    for (int i = 0; i <= (*p1).degree; ++i) {
        for (int j = 0; j <= (*p2).degree; ++j) {
            result.coeffs[result.degree - (i + j)] +=
                (*p1).coeffs[(*p1).degree - i] * (*p2).coeffs[(*p2).degree - j];
        }
    }

    removeLeadingZeros(&result);
    return result;
}

Polynomial multiplyPolynomialByScalar(const Polynomial* p, double scalar) {
    Polynomial result = *p;

    for (int i = 0; i <= result.degree; ++i) {
        result.coeffs[i] *= scalar;
    }

    removeLeadingZeros(&result);
    return result;
}

int dividePolynomials(const Polynomial* dividend, const Polynomial* divisor,
                     Polynomial* quotient, Polynomial* remainder) {
    if ((*divisor).degree == 0 && (*divisor).coeffs[0] == 0.0) {
        return -1;
    }

    *remainder = *dividend;
    initZeroPolynomial(quotient);

    while ((*remainder).degree >= (*divisor).degree) {
        int currentDegree = (*remainder).degree - (*divisor).degree;
        double factor = (*remainder).coeffs[0] / (*divisor).coeffs[0];

        (*quotient).coeffs[currentDegree] = factor;
        (*quotient).degree = ((*quotient).degree > currentDegree) ? (*quotient).degree : currentDegree;

        Polynomial temp;
        initZeroPolynomial(&temp);
        temp.degree = currentDegree;
        temp.coeffs[0] = factor;

        Polynomial tempProduct = multiplyPolynomials(&temp, divisor);
        *remainder = subtractPolynomials(remainder, &tempProduct);
    }

    return 0;
}

Polynomial derivative(const Polynomial* p) {
    Polynomial result;
    initZeroPolynomial(&result);

    if ((*p).degree == 0) {
        return result;
    }

    result.degree = (*p).degree - 1;

    for (int i = 0; i < (*p).degree; ++i) {
        result.coeffs[i] = (*p).coeffs[i] * ((*p).degree - i);
    }

    return result;
}

void polynomialToString(const Polynomial* p, char* buffer, int bufferSize) {
    if ((*p).degree == 0 && (*p).coeffs[0] == 0.0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    int pos = 0;
    bool firstTerm = true;

    for (int i = 0; i <= (*p).degree && pos < bufferSize - 1; ++i) {
        double coeff = (*p).coeffs[i];
        if (coeff == 0.0) continue;

        int power = (*p).degree - i;

        if (!firstTerm) {
            if (coeff > 0 && pos < bufferSize - 3) {
                buffer[pos++] = ' ';
                buffer[pos++] = '+';
                buffer[pos++] = ' ';
            }
            else if (coeff < 0 && pos < bufferSize - 3) {
                buffer[pos++] = ' ';
                buffer[pos++] = '-';
                buffer[pos++] = ' ';
            }
        }
        else if (coeff < 0 && pos < bufferSize - 1) {
            buffer[pos++] = '-';
        }

        double absCoeff = fabs(coeff);
        if ((absCoeff != 1.0 || power == 0) && pos < bufferSize - 1) {
            int written = snprintf(buffer + pos, bufferSize - pos, "%.2f", absCoeff);
            if (written > 0) pos += written;
        }

        if (power > 0 && pos < bufferSize - 1) {
            buffer[pos++] = 'x';
            if (power > 1 && pos < bufferSize - 2) {
                buffer[pos++] = '^';
                int written = snprintf(buffer + pos, bufferSize - pos, "%d", power);
                if (written > 0) pos += written;
            }
        }

        firstTerm = false;
    }
    buffer[pos] = '\0';
}

void parsePolynomial(const char* str, Polynomial* poly) {
    initZeroPolynomial(poly);
    const char* p = str;
    int i = 0;
    bool readingNumber = false;
    char numBuffer[32];
    int numPos = 0;

    while (*p != '\0' && i <= MAX_DEGREE) {
        if ((*p >= '0' && *p <= '9') || *p == '.' || *p == '-') {
            if (!readingNumber) {
                readingNumber = true;
                numPos = 0;
            }
            if (numPos < 31) {
                numBuffer[numPos++] = *p;
            }
        }
        else if (readingNumber) {
            numBuffer[numPos] = '\0';
            (*poly).coeffs[i++] = atof(numBuffer);
            readingNumber = false;
        }
        p++;
    }

    if (readingNumber && i <= MAX_DEGREE) {
        numBuffer[numPos] = '\0';
        (*poly).coeffs[i++] = atof(numBuffer);
    }

    (*poly).degree = i - 1;
    removeLeadingZeros(poly);
}

void displayPolynomialMenu() {
    cout << "\n=== Калькулятор многочленов ===" << endl;
    cout << "1. Сложение многочленов" << endl;
    cout << "2. Вычитание многочленов" << endl;
    cout << "3. Умножение многочленов" << endl;
    cout << "4. Умножение многочлена на число" << endl;
    cout << "5. Деление многочленов в столбик" << endl;
    cout << "6. Вычисление производной от многочлена" << endl;
    cout << "0. Возврат в главное меню" << endl;
    cout << "Выберите операцию: ";
}

void handlePolynomialMenu() {
    Polynomial poly1, poly2, result, quotient, remainder;
    char input[256];
    char output[512];
    double scalar;
    int choice;

    do {
        displayPolynomialMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Введите первый многочлен (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly1);

            cout << "Введите второй многочлен (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly2);

            result = addPolynomials(&poly1, &poly2);
            polynomialToString(&result, output, sizeof(output));
            cout << "Результат: " << output << endl;
            break;

        case 2:
            cout << "Введите первый многочлен (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly1);

            cout << "Введите второй многочлен (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly2);

            result = subtractPolynomials(&poly1, &poly2);
            polynomialToString(&result, output, sizeof(output));
            cout << "Результат: " << output << endl;
            break;

        case 3:
            cout << "Введите первый многочлен (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly1);

            cout << "Введите второй многочлен (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly2);

            result = multiplyPolynomials(&poly1, &poly2);
            polynomialToString(&result, output, sizeof(output));
            cout << "Результат: " << output << endl;
            break;

        case 4:
            cout << "Введите многочлен (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly1);

            cout << "Введите число: ";
            cin >> scalar;
            cin.ignore();

            result = multiplyPolynomialByScalar(&poly1, scalar);
            polynomialToString(&result, output, sizeof(output));
            cout << "Результат: " << output << endl;
            break;

        case 5:
            cout << "Введите делимое (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly1);

            cout << "Введите делитель (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly2);

            if (dividePolynomials(&poly1, &poly2, &quotient, &remainder) == -1) {
                cout << "Ошибка: деление на нулевой многочлен!" << endl;
            }
            else {
                polynomialToString(&quotient, output, sizeof(output));
                cout << "Частное: " << output << endl;
                polynomialToString(&remainder, output, sizeof(output));
                cout << "Остаток: " << output << endl;
            }
            break;

        case 6:
            cout << "Введите многочлен (коэффициенты через пробел): ";
            cin.getline(input, sizeof(input));
            parsePolynomial(input, &poly1);

            result = derivative(&poly1);
            polynomialToString(&result, output, sizeof(output));
            cout << "Производная: " << output << endl;
            break;

        case 0:
            cout << "Возврат в главное меню." << endl;
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 0);
}