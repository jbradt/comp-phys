#include "Gravity.h"

arma::vec gravForce(const arma::vec& pos1, const double mass1, const arma::vec& pos2, const double mass2)
{
    arma::vec sepVec = pos2 - pos1;
    double sepNorm = arma::norm(sepVec);
    return Constants::G_LY * mass1 * mass2 / (pow(sepNorm, 3) + 1e-3) * sepVec;
}

double gravPot(const arma::vec& pos1, const double mass1, const arma::vec& pos2, const double mass2)
{
    double sep = arma::norm(pos2 - pos1);
    return -Constants::G_LY * mass1 * mass2 / sep;
}
