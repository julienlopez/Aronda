#!/bin/bash
mkdir build
cd build
cmake ..
make unit_tests
./unit_tests/unit_tests

ls -lh .
ls -lh ./lib
ls -lh ./lib/CMakeFiles
ls -lh ./lib/CMakeFiles/libAronda.dir

ls -lh ..
ls -lh ../lib
