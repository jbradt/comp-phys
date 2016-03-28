#include <iostream>
#include <armadillo>
#include "Particle.h"
#include "Integration.h"
#include "parser.h"
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>


int main(const int argc, const char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: solar CONFIG_PATH" << std::endl;
        return 1;
    }

    std::string configPath = argv[1];
    YAML::Node config = YAML::LoadFile(configPath);

    std::vector<Particle> planets;
    for (const auto& planetNode : config["planets"]) {
        std::cout << "Creating planet " << planetNode["name"] << std::endl;
        double mass = planetNode["mass"].as<double>();
        arma::vec pos = planetNode["position"].as<arma::vec>();
        arma::vec vel = planetNode["velocity"].as<arma::vec>();
        std::string name = planetNode["name"].as<std::string>();

        planets.emplace_back(mass, pos, vel, name);
    }

    double timestep = 1;
    if (config["timestep"]) {
        timestep = config["timestep"].as<double>();
    }

    arma::uword numIters = 365 * 100;
    if (config["num_iters"]) {
        numIters = config["num_iters"].as<double>();
    }

    std::function<decltype(euler)> integrator = euler;
    if (config["integrator"]) {
        std::string intName = config["integrator"].as<std::string>();
        if (intName == "euler") {
            integrator = euler;
        }
        else if (intName == "verlet") {
            integrator = verlet;
        }
        else if (intName == "rk4") {
            integrator = rk4;
        }
        else {
            std::cerr << "Unknown integrator name " << intName << std::endl;
            return 1;
        }

        std::cout << "Using integrator " << intName << std::endl;
    }

    arma::uword numDims = planets.front().pos.n_elem;

    std::vector<arma::mat> tracks;
    for (size_t p = 0; p < planets.size(); p++) {
        tracks.push_back(arma::mat(numIters, numDims));
    }

    for (arma::uword i = 0; i < numIters; i++) {
        std::vector<State> states (planets.size());

        for (size_t p = 0; p < planets.size(); p++) {
            const auto& pl = planets.at(p);
            auto accelFunc = std::bind(&Particle::findAcceleration, &pl, std::placeholders::_1);
            states.at(p) = euler(accelFunc, pl.pos, pl.vel, timestep);
        }

        for (size_t p = 0; p < planets.size(); p++) {
            planets.at(p).setState(states.at(p));
            tracks.at(p).row(i) = planets.at(p).pos.t();
        }
    }

    for (size_t p = 0; p < planets.size(); p++) {
        tracks.at(p).save(planets.at(p).name + ".csv", arma::csv_ascii);
    }

    return 0;
}
