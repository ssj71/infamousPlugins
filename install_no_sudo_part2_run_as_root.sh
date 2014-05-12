#!/bin/bash

cd src/CellularAutomatonSynth
make install

cd EnvelopeFollower
make install

cd ../Hip2B
make install

cd ../cheap_distortion
make install

echo "install complete!"
