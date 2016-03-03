#!/bin/bash

OUTPUTS_DIR="../outputs"

# Set this to the location of your built binaries
BUILD_DIR="../build/release"
JACOBISOLVE=${BUILD_DIR}/jacobiSolve
ARMASOLVE=${BUILD_DIR}/armaSolve

echo "Making outputs to show convergence of lowest 3 eigenvalues"
${JACOBISOLVE} 10 375 1e-8 1000000 1
mv eigval.csv ${OUTPUTS_DIR}/eigval_lowest3.csv
mv eigvec.csv ${OUTPUTS_DIR}/eigvec_lowest3.csv

${ARMASOLVE} 10 375
mv arma_eigval.csv ${OUTPUTS_DIR}/arma_eigval_lowest3.csv
mv arma_eigvec.csv ${OUTPUTS_DIR}/arma_eigvec_lowest3.csv

echo "Making outputs with varying omega"
OMEGAS=("0.01" "0.5" "1" "5")
for OMEGA in "${OMEGAS[@]}"; do
    echo "Running for omega=${OMEGA}"
    ${JACOBISOLVE} 10 375 1e-8 1000000 2 ${OMEGA}
    mv eigval.csv ${OUTPUTS_DIR}/eigval_2elec_om${OMEGA}.csv
    mv eigvec.csv ${OUTPUTS_DIR}/eigvec_2elec_om${OMEGA}.csv
done
