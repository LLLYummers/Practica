#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <stdexcept>

class Statistics {
public:
    static double calculateProbability(int m, int n);
    static double calculateExpectedValue(const std::vector<double>& values, const std::vector<double>& probabilities);
    static double calculateVariance(const std::vector<double>& values, const std::vector<double>& probabilities);
    static void handleStatisticsMenu();
};

#endif