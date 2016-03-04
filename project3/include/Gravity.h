#ifndef GRAVITY_H
#define GRAVITY_H

#include <armadillo>
#include "Particle.h"
#include <cmath>

arma::vec3 gravForce(const Particle& pa, const Particle& pb);

#endif /* end of include guard: GRAVITY_H */
