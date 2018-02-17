#!/bin/bash
mkdir build
cd build
cmake ..
make unit_tests
./unit_tests/unit_tests
