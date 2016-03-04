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

arma::vec Particle::findNetGravForce() const
{
    arma::vec totalForce (arma::size(pos), arma::fill::zeros);

    for (const Particle* p : instances) {
        if (p == this) continue;
        totalForce += gravForce(pos, mass, p->pos, p->mass);
    }

    return totalForce;
}

void Particle::updatePositionRK4(const double timestep)
{
    // *** This function is not correct at the moment!
    arma::vec origPos = pos;

    arma::vec k1 = findNetGravForce();
    pos += 0.5 * timestep * k1;
    arma::vec k2 = findNetGravForce();
    pos += 0.5 * timestep * k2;
    arma::vec k3 = findNetGravForce();
    pos += timestep * k3;
    arma::vec k4 = findNetGravForce();
    k1.print();

    pos = origPos + (timestep / 6) * (k1 + 2*k2 + 2*k3 + k4);
}

void Particle::updatePositionEuler(const double timestep)
{
    arma::vec force = findNetGravForce();
    vel += force * timestep / mass;
    pos += vel * timestep;
}
