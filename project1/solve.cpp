#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

double sourceFunction(const double x)
{
    return 100 * std::exp(-10 * x);
}

double secondDerivative(const std::function<double(double)>& f, const double x, const double stepSize)
{
    return (f(x+stepSize) - f(x-stepSize) - 2*f(x)) / (stepSize*stepSize);
}

std::vector<double> solveEquation(const std::function<double(double)>& f, const unsigned numPts)
{
    const double a = -1;
    const double c = -1;
    const double stepSize = 1 / (numPts+1);
    std::vector<double> bs (numPts + 2, 2);
    std::vector<double> ws (numPts + 2, 0);
    for (size_t i = 1; i < numPts; i++) {
        ws.at(i) = f(i*stepSize) * stepSize * stepSize;
    }

    for (size_t i = 1; i < numPts; i++) {
        double factor = a / bs.at(i-1);
        bs.at(i) -= factor * c;
        ws.at(i) -= factor * ws.at(i-1);
    }

    for (size_t i = numPts - 1; i > 0; i--) {
        ws.at(i) -= c / bs.at(i+1) * ws.at(i+1);
    }

    return ws;
}

int main(const int argc, const char** argv)
{
    if (argc != 2) {
        std::cerr << "Wrong number of args." << std::endl;
        return 1;
    }

    unsigned numPts = std::atoi(argv[1]);

    auto result = solveEquation(sourceFunction, numPts);
    for (const auto& v : result) {
        std::cout << v << std::endl;
    }
    return 0;
}
