#!/bin/bash

cd src/CellularAutomatonSynth
qmake 
make

cd ..
mkdir -p ../utils
gcc rule.c -o ../utils/rule

cd EnvelopeFollower
qmake 
make

cd ../Hip2B
qmake
make

cd ../Stuck
qmake
make

cd ../PowerCut
qmake
make

cd ../cheap_distortion
make

echo "install halfway complete! now run install_no_sudo_part2 as root."
