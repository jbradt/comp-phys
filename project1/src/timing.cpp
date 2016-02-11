#include <chrono>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

#include "solver.h"

int main(const int argc, const char** argv)
{
    namespace chr = std::chrono;

    unsigned long numPts = 100000;
    int numIters = 20;
    int numPerIter = 10;

    if (argc >= 2) {
        numPts = std::stoul(argv[1]);
    }
    if (argc >= 3) {
        numPerIter = std::stoi(argv[2]);
    }

    std::vector<chr::high_resolution_clock::duration> durations;

    for (int i = -1; i < numIters; i++) {
        auto begin = chr::high_resolution_clock::now();
        for (int j = 0; j < numPerIter; j++) {
            std::vector<double> result = solveEquation(sourceFunction, numPts);
        }
        auto end = chr::high_resolution_clock::now();
        if (i >= 0) durations.push_back(end - begin);
    }

    std::sort(durations.begin(), durations.end());
    auto minDur = durations.front();
    auto maxDur = durations.back();
    auto totalDur = std::accumulate(durations.begin(), durations.end(), chr::high_resolution_clock::duration::zero());

    double minTime = chr::duration_cast<chr::nanoseconds>(minDur).count() * 1e-9 / numPerIter;
    double maxTime = chr::duration_cast<chr::nanoseconds>(maxDur).count() * 1e-9 / numPerIter;
    double meanTime = chr::duration_cast<chr::nanoseconds>(totalDur).count() * 1e-9 / numPerIter / numIters;

    std::cout << "Ran for " << numIters << " iterations with " << numPts << " points." << std::endl;

    std::cout << std::setprecision(4) << std::scientific;
    std::cout << std::setw(8) << "Best: ";
    std::cout << std::setw(6) << minTime << " s\n";
    std::cout << std::setw(8) << "Worst: ";
    std::cout << std::setw(6) << maxTime << " s\n";
    std::cout << std::setw(8) << "Mean: ";
    std::cout << std::setw(6) << meanTime << " s\n";

    return 0;
}
