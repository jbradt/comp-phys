#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <armadillo>
#include <functional>
#include "State.h"

using updateFunc_t = std::function<arma::vec(const arma::vec&)>;

State euler(const updateFunc_t& func, const arma::vec& pos, const arma::vec& vel, const double timestep);
State verlet(const updateFunc_t& func, const arma::vec& pos, const arma::vec& vel, const double timestep);
State rk4(const updateFunc_t& func, const arma::vec& pos, const arma::vec& vel, const double timestep);



#endif /* end of include guard: INTEGRATION_H */
