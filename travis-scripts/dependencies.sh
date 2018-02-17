#!/bin/bash

git clone https://github.com/julienlopez/ETL
git clone https://github.com/Microsoft/GSL

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
sudo apt-get update

sudo apt-cache search gcc-7
sudo apt-cache search g++
sudo apt-cache search gcov

sudo apt-get install -y cmake libboost-all-dev gcc-7 g++-7