#!/bin/bash

cd src/CellularAutomatonSynth
qmake 
make
gksudo make install

cd ..
mkdir -p ../utils
gcc rule.c -o ../utils/rule


echo "install complete!"
