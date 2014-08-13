#CMake file for infamous stuck

cmake_minimum_required(VERSION 2.6)
project (stuck)

set(LV2_INSTALL_DIR /usr/lib/lv2 CACHE PATH "Specifies where the LV2 libraries should be installed")
set(CMAKE_C_FLAGS "-Wall -g -msse2 -mfpmath=sse -ffast-math")

# check for our various libraries
find_package(PkgConfig)
pkg_check_modules(CAIRO cairo)
#pkg_check_modules(JACK jack)
#set(FLTK_SKIP_OPENGL true)
pkg_check_modules(NTK ntk)
#find_package(FLTK)
#find_package(OpenGL)
pkg_check_modules(LV2 REQUIRED lv2>=.0.1.0)

include_directories (${LV2_INCLUDE_DIRS} ${NTK_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS} ../ffffltk ../draw)
link_directories (${LV2_LIBRARY_DIRS} ${NTK_LIBRARY_DIRS} ${CAIRO_LIBRARY_DIRS})

fltk_wrap_ui(stuckUI stuckUI.fl)

# config libraries

add_library(stuck SHARED
  stuck.c
  stuck.h
)

add_library(stuck_ui SHARED
  stuck_ui_main.cxx
  stuck.h
  ${stuckUI_FLTK_UI_SRCS}
)

#set_target_properties(stuck PROPERTIES PREFIX "")

target_link_libraries(stuck ${LV2_LIBRARIES} m)
target_link_libraries(stuck_ui ${LV2_LIBRARIES} ${NTK_LIBRARIES} ${CAIRO_LIBRARIES} m)

# config install
install(TARGETS stuck stuck_ui 
  LIBRARY
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LV2_INSTALL_DIR}/stuck.lv2
)

install (FILES stuck.lv2/manifest.ttl stuck.lv2/stuck.ttl 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LV2_INSTALL_DIR}/stuck.lv2
)
