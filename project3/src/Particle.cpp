#include "Particle.h"

std::set<Particle*> Particle::instances;

Particle::Particle(const double mass0, const arma::vec& pos0, const arma::vec& vel0, const std::string& name0)
: mass(mass0), pos(pos0), vel(vel0), name(name0)
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
    name = std::move(other.name);

    instances.erase(&other);
    instances.insert(this);
}

arma::vec Particle::findNetGravForce(const arma::vec& pos) const
{
    arma::vec totalForce (arma::size(pos), arma::fill::zeros);

    for (const Particle* p : instances) {
        if (p == this) continue;
        totalForce += gravForce(pos, mass, p->pos, p->mass);
    }

    return totalForce;
}

arma::vec Particle::findAcceleration(const arma::vec& pos) const
{
    return findNetGravForce(pos) / mass;
}

void Particle::setState(const State& st)
{
    pos = st.pos;
    vel = st.vel;
}
