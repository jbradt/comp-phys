#include "Cluster.h"

Cluster::Cluster(const size_t num, const double massMean, const double massDev, const double posRad)
{
    state = arma::mat(num, 7);

    state.cols(0, 2) = arma::randn<arma::mat>(num, 3);

    for (arma::uword i = 0; i < num; i++) {
        arma::rowvec v;
        while (true) {
            v = arma::randu<arma::rowvec>(3) * posRad;
            if (arma::norm(v, 2) <= posRad) {
                state(i, arma::span(0, 2)) = v;
                break;
            }
        }
    }

    state.cols(3, 5).fill(0);
    state.col(6) = arma::randn<arma::vec>(num) * massDev + massMean;
}

void updateState(const double timestep)
{

}

void Cluster::print()
{
    state.print();
}
