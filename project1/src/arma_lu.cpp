#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

#include "solver.h"
#include <armadillo>

int main(const int argc, const char** argv)
{
    if (argc != 3) {
        std::cerr << "Wrong number of args." << std::endl;
        return 1;
    }

    unsigned long numPts = std::stoul(argv[1]);
    const double stepSize = findStepSize(0, 1, numPts);

    std::string filepath = argv[2];
    std::ofstream file (filepath, std::ios::out);
    if (!file.good()) {
        std::cerr << "File was not good" << std::endl;
        return 1;
    }

    arma::mat A (numPts + 1, numPts + 1, arma::fill::zeros);
    A.diag(0).fill(2);
    A.diag(1).fill(-1);
    A.diag(-1).fill(-1);

    arma::vec sourceVec (numPts + 1, arma::fill::zeros);
    for (size_t i = 0; i < numPts + 1; i++) {
        sourceVec(i) = sourceFunction(i*stepSize) * stepSize * stepSize;
    }

    arma::vec x (numPts + 1);
    arma::vec y (numPts + 1);

    arma::mat L, U;
    arma::lu(L, U, A);
    y = arma::solve(L, sourceVec);
    x = arma::solve(U, y);

    file << std::setprecision(4) << std::fixed;

    file << std::setw(10) << "x";
    file << std::setw(10) << "Result";
    file << std::setw(10) << "Exact" << std::endl;

    for (size_t i = 0; i < numPts + 2; i++) {
        file << std::setw(10) << i*stepSize;
        file << std::setw(10) << (i > 0 && i < x.size() ? x(i) : 0);
        file << std::setw(10) << exactResult(i*stepSize) << std::endl;
    }
    return 0;
}
