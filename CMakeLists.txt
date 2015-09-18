cmake_minimum_required(VERSION 2.8)

project(infamous-plugins)

set(LIBDIR lib CACHE STRING "Specifies the name of the library path")

foreach(plug casynth envfollower hip2b powerup powercut cheapdist stuck ewham duffer)# lushlife)
    add_subdirectory(src/${plug})
endforeach(plug)

add_executable(infamous-rule
    src/rule.c
)
install(TARGETS infamous-rule
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
