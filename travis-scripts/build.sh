#!/bin/bash
mkdir build
cd build
cmake ..
make unit_tests
./unit_tests/unit_tests

ls -lh .
ls -lh ./lib
ls -lh ./lib/CMakeFiles
ls -lh ..
ls -lh ../lib
