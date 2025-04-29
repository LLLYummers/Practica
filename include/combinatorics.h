#ifndef COMBINATORICS_H
#define COMBINATORICS_H

#include <iostream>

class Combinatorics {
public:
    static long long factorial(int n);
    static long long arrangementsWithoutRepetition(int n, int k);
    static long long arrangementsWithRepetition(int n, int k);
    static long long combinationsWithoutRepetition(int n, int k);
    static long long combinationsWithRepetition(int n, int k);
    static long long permutations(int n);
    static void showMenu();
    static void runCalculator();
};

#endif // COMBINATORICS_H