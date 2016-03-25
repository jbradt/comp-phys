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

State Particle::findNextStateVerlet(const double timestep) const
{
    arma::vec force_i = findNetGravForce(pos);
    arma::vec posNew = pos + timestep * vel + 0.5*timestep*timestep*force_i / mass;
    arma::vec force_ip1 = findNetGravForce(posNew);
    arma::vec velNew = vel + 0.5*timestep*(force_ip1 + force_i) / mass;

    return State {posNew, velNew};
}


// void Particle::updatePositionRK4(const double timestep) const
// {
//     arma::vec k1 = findNetGravForce();
//     pos += 0.5 * timestep * k1;
//     arma::vec k2 = findNetGravForce();
//     pos += 0.5 * timestep * k2;
//     arma::vec k3 = findNetGravForce();
//     pos += timestep * k3;
//     arma::vec k4 = findNetGravForce();
//     k1.print();
//
//     pos = origPos + (timestep / 6) * (k1 + 2*k2 + 2*k3 + k4);
// }



void Particle::setState(const State& st)
{
    pos = st.pos;
    vel = st.vel;
}
