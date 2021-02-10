#!/bin/bash

# g++ main.cpp -o Hubble -L/home/jay/raylib/src/ -lraylib -ldl
cd /home/jay/Hubble/

mkdir build
cd build && cmake ..
cmake --build . 

./Hubble
