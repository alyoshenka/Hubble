#!/bin/bash

# g++ main.cpp -o Hubble -L/home/jay/raylib/src/ -lraylib -ldl
mkdir build
cd build && cmake ..
cmake --build . 

./Hubble
