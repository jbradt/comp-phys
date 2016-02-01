#include "solver.h"

double sourceFunction(const double x)
{
    return 100 * std::exp(-10 * x);
}

double exactResult(const double x)
{
    return 1 - (1 - exp(-10)) * x - exp(-10 * x);
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
