#ifndef PARTICLE_H
#define PARTICLE_H

#include <armadillo>
#include <set>
#include <string>
#include "Gravity.h"
#include "State.h"


class Particle
{
public:
    Particle(const double mass0, const arma::vec& pos0, const arma::vec& vel0, const std::string& name0);
    ~Particle();

    Particle(const Particle&) = delete;
    Particle(Particle&& other);

    arma::vec findNetGravForce(const arma::vec& pos) const;
    arma::vec findAcceleration(const arma::vec& pos) const;

    State findNextStateVerlet(const double timestep) const;
    State findNextStateRK4(const double timestep) const;
    State findNextStateEuler(const double timestep) const;

    void setState(const State& st);

    double mass;
    arma::vec pos;
    arma::vec vel;
    std::string name;

private:
    static std::set<Particle*> instances;
};

#endif /* end of include guard: PARTICLE_H */
