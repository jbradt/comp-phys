#include "Cluster.h"

Cluster::Cluster(const size_t num, const double massMean, const double massDev, const double posRad)
{
    particles.reserve(num);
    arma::vec masses = arma::randn<arma::vec>(num) * massDev + massMean;

    for (size_t i = 0; i < num; i++) {
        arma::vec pos;
        while (true) {
            pos = arma::randu<arma::vec>(3) * posRad;
            if (arma::norm(pos, 2) <= posRad) {
                break;
            }
        }

        particles.emplace_back(masses(i), pos, arma::zeros<arma::vec>(3));
    }
}

std::ostream& operator<<(std::ostream& os, const Cluster& cl)
{
    os << std::setw(10) << "m";
    os << std::setw(10) << "x" << std::setw(10) << "y" << std::setw(10) << "z";
    os << std::setw(10) << "vx" << std::setw(10) << "vy" << std::setw(10) << "vz" << std::endl;
    for (const Particle& p : cl.particles) {
        os << std::setw(10) << p.mass;
        os << std::setw(10) << p.pos(0) << std::setw(10) << p.pos(1) << std::setw(10) << p.pos(2);
        os << std::setw(10) << p.vel(0) << std::setw(10) << p.vel(1) << std::setw(10) << p.vel(2);
        os << std::endl;
    }

    return os;
}
