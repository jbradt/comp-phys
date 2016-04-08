#include "Particle.h"

std::set<Particle*> Particle::instances;

Particle::Particle(const double mass0, const arma::vec& pos0, const arma::vec& vel0)
: mass(mass0), pos(pos0), vel(vel0)
{
    instances.insert(this);
}

Particle::~Particle()
{
    instances.erase(this);
}

Particle::Particle(Particle&& other)
{
    mass = other.mass;
    pos = std::move(other.pos);
    vel = std::move(other.vel);

    instances.erase(&other);
    instances.insert(this);
}

arma::vec Particle::findNetGravForce(const arma::vec& posVec) const
{
    arma::vec totalForce (arma::size(posVec), arma::fill::zeros);

    for (const Particle* p : instances) {
        if (p == this) continue;
        totalForce += gravForce(posVec, mass, p->pos, p->mass);
    }

    return totalForce;
}

arma::vec Particle::findAcceleration(const arma::vec& posVec) const
{
    return findNetGravForce(posVec) / mass;
}

void Particle::setState(const State& st)
{
    pos = st.pos;
    vel = st.vel;
}
