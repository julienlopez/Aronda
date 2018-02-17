#!/bin/bash

CC=gcc-7 && CXX=g++-7

mkdir build
cd build
cmake ..
make unit_tests
./unit_tests/unit_tests

clang++ --version
g++ --version
gcov --version
