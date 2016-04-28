#include <iostream>
#include <armadillo>
#include "Particle.h"
#include "Integration.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "Cluster.h"

int main(const int argc, const char** argv)
{
    if (argc < 7) {
        std::cout << "Usage: cluster NUM_PT M_MEAN M_STD R0 DT NUM_ITERS" << std::endl;
        return 1;
    }

    size_t num_pts = std::stoull(argv[1]);
    double mass_mean = std::atof(argv[2]);
    double mass_std = std::atof(argv[3]);
    double rad0 = std::atof(argv[4]);
    double timestep = std::atof(argv[5]);
    size_t num_iters = std::stoull(argv[6]);

    auto integrator = std::function<decltype(rk4)>(rk4);
    Cluster cl (num_pts, mass_mean, mass_std, rad0, integrator);

    arma::cube snapshots (num_pts, 9, num_iters);
    snapshots.slice(0) = cl.getStateMatrix();

    for (int i = 1; i < num_iters; i++) {
        cl.update(timestep);
        snapshots.slice(i) = cl.getStateMatrix();
    }

    snapshots.save("result.h5", arma::hdf5_binary);

    return 0;
}
