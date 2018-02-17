#!/bin/bash

CC=gcc-7 && CXX=g++-7

ls /usr/bin

clang++ --version
g++ --version
gcov --version

mkdir build
cd build
cmake ..
make unit_tests
./unit_tests/unit_tests
