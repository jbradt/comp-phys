#ifndef CLUSTER_H
#define CLUSTER_H

#include <armadillo>
#include <vector>
#include <iostream>
#include <iomanip>
#include <functional>

#include "Particle.h"
#include "State.h"

using updateFunc_t = std::function<arma::vec(const arma::vec&)>;
using intFunc_t = std::function<State(const updateFunc_t&, const arma::vec&,
                                      const arma::vec&, const double)>;

class Cluster
{
public:
    Cluster(const size_t num, const double massMean, const double massDev, const double posRad,
            const intFunc_t integrator);

    void update(const double timestep);

    arma::mat getPositionMatrix() const;

    friend std::ostream& operator<<(std::ostream& os, const Cluster& cl);

private:
    std::vector<Particle> particles;
    intFunc_t integrator;
};

#endif /* end of include guard: CLUSTER_H */
