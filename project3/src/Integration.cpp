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
