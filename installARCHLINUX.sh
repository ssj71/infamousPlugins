#!/bin/bash

cd src/CellularAutomatonSynth
qmake-qt4 
make
sudo make install

cd ..
mkdir -p ../utils
gcc rule.c -o ../utils/rule

cd EnvelopeFollower
qmake-qt4 
make
sudo make install

cd ../Hip2B
qmake-qt4
make
sudo make install

cd ../Stuck
qmake-qt4
make
sudo make install

cd ../PowerCut
qmake-qt4
make
sudo make install

cd ../cheap_distortion
make
sudo make install

echo "install complete!"
