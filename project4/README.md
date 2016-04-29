# Project 4

This directory contains the source code and report for the fourth project.

## Compiling

The recommended way to build the code is:

```bash
cd /path/to/project4
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

This requires CMake, Armadillo, and the [HDF5] library to be installed. (HDF5 is used for output.)

## Running

Compiling will produce a binary called `cluster` which can be run as

```bash
cluster NUM_PT M_MEAN M_STD R0 DT NUM_ITERS
```
The parameters used here are:
- `NUM_PT` - The number of particles to simulate
- `M_MEAN` - The mean of the normal mass distribution, in solar masses
- `M_STD` - The standard deviation of the normal mass distribution, in solar masses
- `R0` - The radius of the uniform distribution of initial positions, in light-years
- `DT` - The time step, in years
- `NUM_ITERS` - The number of time steps to simulate

The program will output a file in the [HDF5] format. Specifically, the data is written using Armadillo's `save` function with the format flag `arma::hdf5_binary`. This creates a dataset called "dataset" within the file, with axes [iteration, variable, particle number]. The variables written (the second axis) are [x, y, z, vx, vy, vz, mass, kinetic energy, potential energy].

The data can be read in Python with the `h5py` package by doing, for example,
```python
with h5py.File('/path/to/result.h5') as f:
    data = f['dataset'][:]  # This reads the full dataset into memory
pos = data[:, :3]
kine = data[:, 7]
pot = data[:, 8]
```

## Sample outputs

Due to the large size of the output files, I have not included one in this repository. However, the plots in the final report were created from data run with the following call to the program:
```bash
cluster 500 10 1 20 100000 2000
```
Naturally, every run will produce slightly different output due to the use of random numbers.

## Report

The final report is in the file `writeup/project4.pdf`. Please excuse the horrible layout as LaTeX was not pleased with the number of plots I included.

[HDF5]: https://www.hdfgroup.org/HDF5/
