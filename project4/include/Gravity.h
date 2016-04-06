#ifndef GRAVITY_H
#define GRAVITY_H

#include <armadillo>
#include <cmath>
#include "Constants.h"

arma::vec gravForce(const arma::vec& pos1, const double mass1, const arma::vec& pos2, const double mass2);

#endif /* end of include guard: GRAVITY_H */
