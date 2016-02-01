#include <vector>
#include <functional>
#include <cmath>
#include <string>

double sourceFunction(const double x);
double exactResult(const double x);
inline double findStepSize(const double lb, const double ub, const unsigned long numPts) { return (ub - lb) / (numPts + 1); }
std::vector<double> solveEquation(const std::function<double(double)>& f, const unsigned long numPts);
