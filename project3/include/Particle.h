#ifndef PARTICLE_H
#define PARTICLE_H

#include <armadillo>
#include <set>
#include "Gravity.h"

class Particle
{
public:
    Particle(const double mass0, const arma::vec& pos0, const arma::vec& vel0);
    ~Particle();

    arma::vec findNetGravForce() const;
    void updatePositionRK4(const double timestep);
    void updatePositionEuler(const double timestep);

    double mass;
    arma::vec pos;
    arma::vec vel;

private:
    static std::set<Particle*> instances;
};

#endif /* end of include guard: PARTICLE_H */
