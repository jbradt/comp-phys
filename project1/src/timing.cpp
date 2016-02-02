#include <chrono>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

#include "solver.h"

int main()
{
    namespace chr = std::chrono;

    unsigned long numPts = 100000;
    int numIters = 20;

    std::vector<chr::high_resolution_clock::duration> durations;

    std::vector<double> result = solveEquation(sourceFunction, numPts);

    for (int i = 0; i < numIters; i++) {
        auto begin = chr::high_resolution_clock::now();
        result = solveEquation(sourceFunction, numPts);
        auto end = chr::high_resolution_clock::now();
        durations.push_back(end - begin);
    }

    std::sort(durations.begin(), durations.end());
    auto minDur = durations.front();
    auto maxDur = durations.back();
    auto totalDur = std::accumulate(durations.begin(), durations.end(), chr::high_resolution_clock::duration::zero());

    std::cout << "Ran for " << numIters << " iterations with " << numPts << " points." << std::endl;

    std::cout << std::setprecision(4);
    std::cout << std::setw(8) << "Best: ";
    std::cout << std::setw(6) << chr::duration_cast<chr::microseconds>(minDur).count() << " µs\n";
    std::cout << std::setw(8) << "Worst: ";
    std::cout << std::setw(6) << chr::duration_cast<chr::microseconds>(maxDur).count() << " µs\n";
    std::cout << std::setw(8) << "Mean: ";
    std::cout << std::setw(6) << chr::duration_cast<chr::microseconds>(totalDur).count() / numIters << " µs\n";

    return 0;
}
