#ifndef CLUSTER_H
#define CLUSTER_H

#include <armadillo>
#include <vector>
#include <iostream>
#include <iomanip>

#include "Particle.h"

class Cluster
{
public:
    Cluster(const size_t num, const double massMean, const double massDev, const double posRad);

    friend std::ostream& operator<<(std::ostream& os, const Cluster& cl);

private:
    std::vector<Particle> particles;
};

#endif /* end of include guard: CLUSTER_H */
