# Project 1

The code and results for the first project are in this directory.

## Compiling

For convenience, I used CMake to manage building the project. You'll need CMake version 3.1 or newer to compile the code. Additionally, the Armadillo library is required to build the last two targets.

The recommended way to build the code is:

    cd /path/to/project1
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make

This will make five executables:

- `solve` - This is the main program, which solves the equation and outputs the solution. Call it like `./solve NUM_PTS OUT_PATH`, where `NUM_PTS` is the number of mesh points to use, and `OUT_PATH` is the output path for the results.
- `test_solver` - This runs unit tests on the solver functions.
- `time_solver` - This runs the solver for a number of iterations and reports how long it takes.
- `arma_lu` - This solves the equation using the `arma::lu` and `arma::solve` functions for comparison.
- `time_arma_lu` - This times the solution using the Armadillo functions.


## Outputs

There are example outputs in the directory `outputs/solver_outputs` for different numbers of points. The files called `res*.txt` have outputs from the `solve` program, while the files called `arma*.txt` have outputs from the `arma_lu` program.

## Report

The final report for the project is in the file `report/project1.pdf`.
