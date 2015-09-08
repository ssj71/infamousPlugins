cmake_minimum_required(VERSION 2.8)

foreach(plug casynth envfollower hip2b powerup powercut cheapdist stuck ewham duffer)# lushlife)
    add_subdirectory(src/${plug})
endforeach(plug)
