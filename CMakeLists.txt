cmake_minimum_required(VERSION 2.8)

project(infamous-plugins)

set(LIBDIR lib CACHE STRING "Specifies the name of the library path")
#set(CMAKE_C_FLAGS "-Wall -g -std=c99 -msse2 -mfpmath=sse -ffast-math")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c99 -msse2 -mfpmath=sse -ffast-math")

# check for our various libraries
find_package(PkgConfig)
pkg_check_modules(CAIRO cairo)
pkg_check_modules(NTK ntk)
pkg_check_modules(LV2 REQUIRED lv2>=.0.1.0)
pkg_check_modules(FFTW fftw3f)
#pkg_check_modules(ZRESAMPLER zitaresampler)
#find_package(ZRESAMPLER zita-resampler)

find_program(FLTK_FLUID_EXECUTABLE ntk-fluid)
if (FLTK_FLUID_EXECUTABLE STREQUAL "FLTK_FLUID_EXECUTABLE-NOTFOUND")
  message(FATAL_ERROR "ntk-fluid is required")
endif()

include_directories(${LV2_INCLUDE_DIRS} ${FFTW_INCLUDE_DIRS} ${NTK_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS} src/ffffltk src/draw)
link_directories(${LV2_LIBRARY_DIRS} ${FFTW_LIBRARY_DIRS} ${NTK_LIBRARY_DIRS} ${CAIRO_LIBRARY_DIRS})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

foreach(plug casynth envfollower hip2b powerup powercut cheapdist stuck ewham duffer)# lushlife)
    add_subdirectory(src/${plug})
endforeach(plug)
