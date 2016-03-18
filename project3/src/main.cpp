#include <iostream>
#include <armadillo>
#include "Particle.h"
#include "parser.h"
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <memory>


int main(const int argc, const char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: solar CONFIG_PATH" << std::endl;
        return 1;
    }

    std::string configPath = argv[1];
    YAML::Node config = YAML::LoadFile(configPath);

    std::vector<std::unique_ptr<Particle>> planets;
    for (const auto& planetNode : config["planets"]) {
        std::cout << "Creating planet " << planetNode["name"] << std::endl;
        double mass = planetNode["mass"].as<double>();
        arma::vec pos = planetNode["position"].as<arma::vec>();
        arma::vec vel = planetNode["velocity"].as<arma::vec>();
        std::string name = planetNode["name"].as<std::string>();

        std::unique_ptr<Particle> ptr (new Particle {mass, pos, vel, name});
        planets.push_back(std::move(ptr));
    }

    double timestep = 1;
    arma::uword numIters = 365 * 20;

    arma::uword numDims = planets.front()->pos.n_elem;

    std::vector<arma::mat> tracks;
    for (size_t p = 0; p < planets.size(); p++) {
        tracks.push_back(arma::mat(numIters, numDims));
    }

    for (arma::uword i = 0; i < numIters; i++) {
        std::vector<State> states (planets.size());

        for (size_t p = 0; p < planets.size(); p++) {
            states.at(p) = planets.at(p)->findNextStateEuler(timestep);
        }

        for (size_t p = 0; p < planets.size(); p++) {
            planets.at(p)->setState(states.at(p));
            tracks.at(p).row(i) = planets.at(p)->pos.t();
        }
    }

    for (size_t p = 0; p < planets.size(); p++) {
        tracks.at(p).save(planets.at(p)->name + ".csv", arma::csv_ascii);
    }

    return 0;
}
