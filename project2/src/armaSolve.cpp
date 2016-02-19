#include <iostream>
#include <fstream>
#include <armadillo>

double potential(const double r)
{
    return r*r;
}

int main(const int argc, const char** argv)
{
    if (argc < 3) {
        puts("Usage: armaSolve MAX_RHO NUM_PTS");
        return 1;
    }

    double maxRho = atof(argv[1]);
    arma::uword matSize = static_cast<arma::uword>(std::stoul(argv[2]));

    double stepSize = maxRho / matSize;

    // Allocate matrices
    arma::mat mat (matSize, matSize, arma::fill::zeros);
    arma::mat eigvec (matSize, matSize, arma::fill::eye);
    arma::vec eigval (matSize, arma::fill::zeros);

    // Fill matrices
    for (arma::uword i = 0; i < matSize; i++) {
        // Main diagonal elements
        double rho = (i+1) * stepSize;
        double pot = potential(rho);
        mat(i,i) = (2 / (stepSize * stepSize)) + pot;

        // Upper and lower diagonals
        double offDiagEl = -1 / (stepSize * stepSize);
        if (i < matSize - 1) {
            mat(i,i+1) = offDiagEl;
            mat(i+1,i) = offDiagEl;
        }
    }

    mat.save("init_mat.csv", arma::csv_ascii);

    arma::eig_sym(eigval, eigvec, mat);

    eigval.save("arma_eigval.csv", arma::csv_ascii);
    eigvec.save("arma_eigvec.csv", arma::csv_ascii);

    return 0;
}
