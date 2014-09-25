cmake_minimum_required(VERSION 2.8)
include(ExternalProject)


foreach(plug CellularAutomatonSynth EnvelopeFollower Hip2B PowerUp PowerCut CheapDistortion Stuck)
    ExternalProject_Add( ${plug}
    #  PREFIX ${CMAKE_SOURCE_DIR}
      SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/${plug}
    #  BUILD_DIR ${CMAKE_BUILD_DIR}
      DOWNLOAD_COMMAND ""
    )
endforeach(plug)
