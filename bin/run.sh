#!/bin/bash

# run file.
# if any cmd line arg is given, run via gdb

IC_FILE=IC_SPH_uniform_3D.dat
make

if [[ $# > 0 ]]; then
    gdb --args ./sph paramfile.txt $IC_FILE
else
    ./sph paramfile.txt $IC_FILE
fi
