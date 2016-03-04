#include "Gravity.h"

arma::vec3 gravForce(const Particle& pa, const Particle& pb)
{
    const double G = 6.67e-11;
    arma::vec3 sepVec = pb.getPos() - pa.getPos();
    double sepNorm = arma::norm(sepVec);
    return G * pb.getMass() * pa.getMass() / pow(sepNorm, 3) * sepVec;
}
