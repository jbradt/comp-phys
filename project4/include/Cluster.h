#ifndef CLUSTER_H
#define CLUSTER_H

#include <armadillo>
#include "Gravity.h"

class Cluster
{
public:
    Cluster(const size_t num, const double massMean, const double massDev, const double posRad);

    void print();
private:
    arma::mat state;
};

#endif /* end of include guard: CLUSTER_H */
