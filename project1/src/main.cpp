#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

#include "solver.h"

int main(const int argc, const char** argv)
{
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

    std::vector<double> result = solveEquation(sourceFunction, numPts);

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
