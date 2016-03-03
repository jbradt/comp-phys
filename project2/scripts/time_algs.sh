#!/bin/bash

OUTPUTS_DIR="../outputs"

# Set this to the location of your built binaries
BUILD_DIR="../build/release"
JACOBISOLVE=${BUILD_DIR}/jacobiSolve
ARMASOLVE=${BUILD_DIR}/armaSolve

NUMPTS=100

NUMS=("10" "20" "40" "60" "80" "100" "120" "140" "160" "180" "200" "220" "240" "260" "280" "300")

echo "N,time"
for NUM in "${NUMS[@]}"; do
    $JACOBISOLVE 10 $NUM 1e-8 1000000 1 1> output.tmp 2> timing.tmp
    REGEX="([0-9]+)"
    if [[ $RES =~ $REGEX ]]; then
        echo "$NUM,${BASH_REMATCH[1]}"
    fi
done;
