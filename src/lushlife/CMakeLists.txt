#CMake file for infamous stuck

set(PLUGIN "lushlife")

include_directories(.)

#fltk_wrap_ui(${PLUGIN}_ui ${PLUGIN}_ui.fl)

# config libraries

add_library(${PLUGIN} SHARED
  lushlife.cc
  lushlife.h
  retuner.cc
  retuner.h
  lfo.cc
  lfo.h
)

#add_library(${PLUGIN}_ui SHARED
#  lushlife.h
#  lushlife_ui_main.cxx
#  ${${PLUGIN}_ui_FLTK_UI_SRCS}
#)

set_target_properties(${PLUGIN} PROPERTIES PREFIX "")
#set_target_properties(${PLUGIN}_ui PROPERTIES PREFIX "")

set_target_properties(${PLUGIN} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
#set_target_properties(${PLUGIN}_ui PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)

target_link_libraries(${PLUGIN} ${LV2_LIBRARIES} ${FFTW_LIBRARIES} m zita-resampler)
#target_link_libraries(${PLUGIN}_ui ${LV2_LIBRARIES} ${NTK_LIBRARIES} ${CAIRO_LIBRARIES} m)

# config install
install(TARGETS ${PLUGIN} # ${PLUGIN}_ui
  LIBRARY
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/lv2/${PLUGIN}.lv2
)

install (FILES manifest.ttl ${PLUGIN}.ttl 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/lv2/${PLUGIN}.lv2
)
