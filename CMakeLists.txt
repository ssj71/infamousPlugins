cmake_minimum_required(VERSION 2.8)

foreach(plug CellularAutomatonSynth EnvelopeFollower Hip2B PowerUp PowerCut CheapDistortion Stuck)
    add_subdirectory(src/${plug})
endforeach(plug)
