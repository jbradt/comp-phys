# Project 2

This directory contains the source code and report for the second project.

## Compiling

The recommended way to build the code is:

    cd /path/to/project2
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make

This requires CMake and Armadillo to be installed.

Four binaries will be built:

1. `jacobiSolve` - This is the main code for the project. It solves the one- or
    two-electron problem for provided values of rho and omega.

    Call this code as:

        jacobiSolve MAX_RHO NUM_PTS TOL MAX_ITER NUM_ELEC [OMEGA]

    where `MAX_RHO` is the maximum value of rho, `NUM_PTS` is the number of grid points,
    `TOL` is the tolerance to use, `MAX_ITER` is the maximum number of transformations
    to perform, and `NUM_ELEC` is either 1 or 2. `OMEGA` only needs to be given if
    `NUM_ELEC == 2`.

    This code will run and produce the output files `eigvec.csv` and `eigval.csv` in the
    current directory. `eigval.csv` contains the eigenvalues, separated by newlines.
    `eigvec.csv` contains a matrix of the eigenvectors, separated by commas. Each column
    corresponds to an eigenvector.

2. `armaSolve` - A similar code built with Armadillo's `eig_sym` function to solve the
    problem. The usage is like above, but with fewer arguments:

        armaSolve MAX_RHO NUM_PTS

    The outputs are the same as above, but with "arma_" prefixed to the file names.

3. `testJacobi` - A set of unit tests for `jacobiSolve`.

4. `timeOffdiag` - A small piece of code that prints how long the `offDiag` function
    takes to execute. This was mainly useful for testing.

## Outputs

Some sample outputs can be found in the folder `outputs`. Most of these can be reproduced by running the scripts found in `scripts`.

## Report

The final report is in the file `writeup/project2.pdf`.
