#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <functional>
#include <cmath>
#include <string>
#include <chrono>

double sourceFunction(const double x)
{
    return 100 * std::exp(-10 * x);
}

double exactResult(const double x)
{
    return 1 - (1 - exp(-10)) * x - exp(-10 * x);
}

inline double findStepSize(const double lb, const double ub, const unsigned long numPts)
{
    return (ub - lb) / (numPts + 1);
}

std::vector<double> solveEquation(const std::function<double(double)>& f, const unsigned long numPts)
{
    const double a = -1;
    const double c = -1;
    const double stepSize = findStepSize(0, 1, numPts);
    std::vector<double> bs (numPts + 2, 2);
    std::vector<double> ws (numPts + 2, 0);
    for (size_t i = 1; i < numPts; i++) {
        ws.at(i) = f(i*stepSize) * stepSize * stepSize;
    }

    // Forward substitution
    for (size_t i = 1; i < numPts; i++) {
        double factor = a / bs.at(i-1);
        bs.at(i) -= factor * c;
        ws.at(i) -= factor * ws.at(i-1);
    }

    // Backward substitution
    for (size_t i = numPts - 1; i > 0; i--) {
        ws.at(i) -= c / bs.at(i+1) * ws.at(i+1);
    }

    return ws;
}

int main(const int argc, const char** argv)
{
    namespace chr = std::chrono;

    if (argc != 3) {
        std::cerr << "Wrong number of args." << std::endl;
        return 1;
    }

    unsigned long numPts = std::stoul(argv[1]);
    std::string filepath = argv[2];

    std::ofstream file (filepath, std::ios::out);
    if (!file.good()) {
        std::cerr << "File was not good" << std::endl;
        return 1;
    }

    auto begin = chr::high_resolution_clock::now();
    std::vector<double> result = solveEquation(sourceFunction, numPts);
    auto end = chr::high_resolution_clock::now();
    std::cout << "Solved in ";
    std::cout << chr::duration_cast<chr::microseconds>(end - begin).count();
    std::cout << " µs" << std::endl;

    const double stepSize = findStepSize(0, 1, numPts);

    file << std::setprecision(4) << std::fixed;

    file << std::setw(10) << "x";
    file << std::setw(10) << "Result";
    file << std::setw(10) << "Exact" << std::endl;

    for (size_t i = 0; i < result.size(); i++) {
        file << std::setw(10) << i*stepSize;
        file << std::setw(10) << result.at(i);
        file << std::setw(10) << exactResult(i*stepSize) << std::endl;
    }
    return 0;
}
