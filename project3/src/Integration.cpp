#include "Integration.h"

State euler(const updateFunc_t& func, const arma::vec& pos, const arma::vec& vel, const double timestep)
{
    arma::vec deltaV = func(pos);
    // deltaV.print();
    State result;
    result.vel = vel + deltaV * timestep;
    result.pos = pos + result.vel * timestep;
    return result;
}

State verlet(const updateFunc_t& func, const arma::vec& pos, const arma::vec& vel, const double timestep)
{
    arma::vec accel_i = func(pos);
    arma::vec posNew = pos + timestep * vel + 0.5*timestep*timestep*accel_i;
    arma::vec accel_ip1 = func(posNew);
    arma::vec velNew = vel + 0.5*timestep*(accel_ip1 + accel_i);

    return State {posNew, velNew};
}
