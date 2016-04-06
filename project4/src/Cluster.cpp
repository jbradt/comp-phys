#include "Cluster.h"

Cluster::Cluster(const size_t num, const double massMean, const double massDev, const double posRad)
{
    state = arma::mat(num, 7);

    state.cols(0, 2) = arma::randn<arma::mat>(num, 3);
    state.cols(3, 5).fill(0);
    state.col(6) = arma::randn<arma::vec>(num) * massDev + massMean;
}

void Cluster::print()
{
    state.print();
}
