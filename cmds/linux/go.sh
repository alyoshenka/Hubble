#!/bin/bash

# g++ main.cpp -o Hubble -L/home/jay/raylib/src/ -lraylib -ldl
cd /home/jay/Hubble/

mkdir build
cd build && cmake /home/jay/Hubble
cmake --build . 

/home/jay/Hubble/build/Hubble
