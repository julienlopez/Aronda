#!/bin/bash

git clone https://github.com/julienlopez/ETL
git clone https://github.com/Microsoft/GSL

sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install -y cmake libboost-all-dev
sudo apt-cache search gcc
sudo apt-cache search gcov