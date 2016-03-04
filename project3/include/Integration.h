#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <armadillo>

arma::vec rk4(const Particle& p, const double timestep);

#endif /* end of include guard: INTEGRATION_H */
