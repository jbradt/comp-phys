# Project 3

This directory contains the source code and report for the third project.

## Compiling

The recommended way to build the code is:

```bash
cd /path/to/project3
git submodule update --init --recursive    # this only needs to be done once
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

This requires CMake and Armadillo to be installed. The project also depends on [yaml-cpp](https://github.com/jbeder/yaml-cpp) for parsing config files, but this will be downloaded automatically by the `git submodule update --init --recursive` function above, and will be built automatically by CMake.

## Running

Compiling will produce a binary called `solar` which can be run as

```bash
    solar CONFIG_PATH
```
where `CONFIG_PATH` is the path to a YAML config file like in the `configs` directory. The program will output a CSV file for each body defined in the config file. The CSV file has the columns `(x, y, z, vx, vy, vz)` if the position is specified in 3D, or `(x, y, vx, vy)` if it is given in 2D.

## Configs

The `configs` directory contains a few config files that were used to produce the results shown in the report. These are in the [YAML](https://en.wikipedia.org/wiki/YAML) language. The basic format is:

```yaml
---
timestep: 1.0    # Time step in days
num_iters: 1460  # Number of time steps to run
integrator: rk4  # One of euler, verlet, or rk4. Case-sensitive.

planets:
    - name: Earth            # Name of the planet / other body
      mass: 3.0e-6           # Mass in units of solar mass
      position: [1.0, 0]     # Position in au. Can be 2D or 3D.
      velocity: [0, 0.0243]  # Velocity in au/d. Can be 2D or 3D.
      fixed: False           # Optional. If True, the body is not allowed to move.

    # And more entries for other planets...
```

## Sample outputs

Outputs for each config file in the `configs` directory can be found in the `outputs` directory.

## Report

The final report is in the file `writeup/project3.pdf`.
