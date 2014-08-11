#!/bin/bash

which sudo && run_as_root="sudo" || run_as_root="su -l root -c"
which qmake && qmake_bin="qmake" || qmake_bin="qmake-qt4"

plugins="CellularAutomatonSynth EnvelopeFollower Hip2B Stuck PowerCut PowerUp"

for plugin in $plugins
do
  $qmake_bin -o src/$plugin/Makefile src/$plugin/$plugin.pro
  make -C src/$plugin
  $run_as_root make -C src/$plugin install
done

gcc src/rule.c -o src/infamous-rule
$run_as_root install -m 755 src/infamous-rule /usr/bin

make -C src/cheap_distortion
$run_as_root make -C src/cheap_distortion install

echo "install complete!"
