#!/bin/bash


cd bin && cmake ..
cmake --build .
mv ./Midas ./out/Midas
cd out
./Midas
