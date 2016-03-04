#include <iostream>
#include <armadillo>
#include "Particle.h"

int main()
{
    Particle sun (1.0, arma::zeros<arma::vec>(2), arma::zeros<arma::vec>(2));
    Particle earth (3.0e-6, arma::vec {1.0, 0}, arma::vec {0, 0.0172});
    Particle jupiter (9.54e-4, arma::vec {5.427, 0}, arma::vec {0, 0.00754});

    double timestep = 1;
    arma::uword numIters = 365 * 20;

    arma::mat earthTrack (numIters, earth.pos.n_elem);
    arma::mat jupiterTrack (numIters, jupiter.pos.n_elem);

    for (arma::uword i = 0; i < numIters; i++) {
        earth.updatePositionEuler(timestep);
        jupiter.updatePositionEuler(timestep);
        earthTrack.row(i) = arma::conv_to<arma::rowvec>::from(earth.pos);
        jupiterTrack.row(i) = arma::conv_to<arma::rowvec>::from(jupiter.pos);
    }

    earthTrack.save("earthPos.csv", arma::csv_ascii);
    jupiterTrack.save("jupPos.csv", arma::csv_ascii);

    return 0;
}
