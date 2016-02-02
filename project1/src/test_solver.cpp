#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "solver.h"
#include <algorithm>

TEST_CASE("Step size is logical")
{
    const unsigned long numPts = 100;
    const double minVal = 0;
    const double maxVal = 1;
    const double stepSize = findStepSize(minVal, maxVal, numPts);

    REQUIRE(std::abs(stepSize*(numPts+1) - maxVal) < stepSize);
}

TEST_CASE("Solver converges to correct result for small step sizes")
{
    const unsigned long numPts = 100000;
    const double stepSize = findStepSize(0, 1, numPts);

    std::vector<double> expected (numPts + 2);
    for (size_t i = 0; i < expected.size(); i++) {
        expected.at(i) = exactResult(i*stepSize);
    }

    std::vector<double> result = solveEquation(sourceFunction, numPts);

    REQUIRE(result.size() == numPts + 2);
    for (size_t i = 0; i < numPts; i++) {
        REQUIRE(std::abs(result.at(i) - expected.at(i)) < 1e-3);
    }
}
