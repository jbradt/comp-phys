#ifndef PARTICLE_H
#define PARTICLE_H

#include <armadillo>

class Particle
{
public:
    Particle(const double mass0, const arma::vec3& pos0, const arma::vec3& vel0)
    : mass(mass0), pos(pos0), vel(vel0) {}

    double getMass() const { return mass; }
    arma::vec3 getPos() const { return pos; }
    arma::vec3 getVel() const { return vel; }

    void setPos(const arma::vec3& newPos) { pos = newPos; }
    void setVel(const arma::vec3& newVel) { vel = newVel; }

private:
    double mass;
    arma::vec3 pos;
    arma::vec3 vel;
};

#endif /* end of include guard: PARTICLE_H */
