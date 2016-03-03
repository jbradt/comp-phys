#!/bin/bash

OUTPUTS_DIR="../outputs"

# Set this to the location of your built binaries
BUILD_DIR="../build/release"
JACOBISOLVE=${BUILD_DIR}/jacobiSolve
ARMASOLVE=${BUILD_DIR}/armaSolve

NUMS=("10" "20" "40" "60" "80" "100" "120" "140" "160" "180" "200" "220" "240" "260" "280" "300")

echo "N,iters,time,arma_time"
for NUM in "${NUMS[@]}"; do
    { time $JACOBISOLVE 10 $NUM 1e-8 1000000 1; } 1> "res.tmp" 2> "timing.tmp"
    REGEX1="([0-9]+)"
    REGEX2="([0-9]*\.[0-9]*)"

    [[ "$(cat res.tmp)" =~ $REGEX1 ]]
    NUMITERS=${BASH_REMATCH[1]}

    [[ "$(grep real timing.tmp)" =~ $REGEX2 ]]
    TIME=${BASH_REMATCH[1]}

    { time $ARMASOLVE 10 $NUM; } 1> "res.tmp" 2> "timing.tmp"

    [[ "$(grep real timing.tmp)" =~ $REGEX2 ]]
    ARMATIME=${BASH_REMATCH[1]}

    echo "$NUM,$NUMITERS,$TIME,$ARMATIME"

    rm -f res.tmp
    rm -f timing.tmp
done;
