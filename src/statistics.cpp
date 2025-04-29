#include "statistics.h"
#include <iostream>
#include <limits>
#include <numeric>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

using namespace std;

double Statistics::calculateProbability(int m, int n) {
    if (n <= 0) throw std::invalid_argument("n должно быть положительным");
    if (m < 0 || m > n) throw std::invalid_argument("m должно быть 0 <= m <= n");
    return static_cast<double>(m) / n;
}

double Statistics::calculateExpectedValue(const vector<double>& values, const vector<double>& probs) {
    if (values.size() != probs.size()) 
        throw std::invalid_argument("Разные размеры массивов");
    
    double sum_probs = std::accumulate(probs.begin(), probs.end(), 0.0);
    if (fabs(sum_probs - 1.0) > 1e-6)
        throw std::invalid_argument("Сумма вероятностей должна быть равна 1");
    
    double sum = 0.0;
    for (size_t i = 0; i < values.size(); ++i) {
        sum += values[i] * probs[i];
    }
    return sum;
}

double Statistics::calculateVariance(const vector<double>& values, const vector<double>& probs) {
    double expected = calculateExpectedValue(values, probs);
    double variance = 0.0;
    
    for (size_t i = 0; i < values.size(); ++i) {
        double diff = values[i] - expected;
        variance += probs[i] * diff * diff;
    }
    return variance;
}

void Statistics::handleStatisticsMenu() {
    int choice;
    do {
        cout << "\nМеню статистики:\n"
             << "1. Вероятность m/n\n"
             << "2. Мат. ожидание\n"
             << "3. Дисперсия\n"
             << "0. Назад\n"
             << "Выбор: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    int m, n;
                    cout << "Введите m и n: ";
                    cin >> m >> n;
                    cout << "Вероятность: " << calculateProbability(m, n) << endl;
                    break;
                }
                case 2: {
                    size_t count;
                    cout << "Введите количество значений: ";
                    cin >> count;
                    
                    vector<double> values(count);
                    vector<double> probs(count);
                    
                    cout << "Введите значения через пробел: ";
                    for (size_t i = 0; i < count; ++i)
                        cin >> values[i];
                    
                    cout << "Введите вероятности через пробел: ";
                    for (size_t i = 0; i < count; ++i)
                        cin >> probs[i];
                    
                    cout << "Мат. ожидание: " << calculateExpectedValue(values, probs) << endl;
                    break;
                }
                case 3: {
                    size_t count;
                    cout << "Введите количество значений: ";
                    cin >> count;
                    
                    vector<double> values(count);
                    vector<double> probs(count);
                    
                    cout << "Введите значения через пробел: ";
                    for (size_t i = 0; i < count; ++i)
                        cin >> values[i];
                    
                    cout << "Введите вероятности через пробел: ";
                    for (size_t i = 0; i < count; ++i)
                        cin >> probs[i];
                    
                    cout << "Дисперсия: " << calculateVariance(values, probs) << endl;
                    break;
                }
            }
        } catch (const std::exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);
}
