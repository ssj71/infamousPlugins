#!/bin/bash

cd src/CellularAutomationSynth
qmake 
make
gksudo make install

cd ..
gcc rule.c -o ../rule


echo "install complete!"
