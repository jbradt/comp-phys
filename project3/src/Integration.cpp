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

State rk4(const updateFunc_t& func, const arma::vec& pos, const arma::vec& vel, const double timestep)
{
    arma::vec k1v = func(pos);
    arma::vec k1p = vel;
    arma::vec k2v = func(pos + k1p * timestep / 2);
    arma::vec k2p = (vel + k1v * timestep / 2);
    arma::vec k3v = func(pos + k2p * timestep / 2);
    arma::vec k3p = (vel + k2v * timestep / 2);
    arma::vec k4v = func(pos + k3p * timestep);
    arma::vec k4p = (vel + k3v * timestep);

    arma::vec newVel = vel + (timestep / 6) * (k1v + 2*k2v + 2*k3v + k4v);
    arma::vec newPos = pos + (timestep / 6) * (k1p + 2*k2p + 2*k3p + k4p);

    return State {newPos, newVel};
}
