#CMake file for infamous stuck

set(PLUGIN "casynth")

# check for our various libraries

include_directories(.)

fltk_wrap_ui(${PLUGIN}_ui ${PLUGIN}_ui.fl)

# config libraries

add_library(${PLUGIN} SHARED
  casynth.c
  waves.c
  note.c
)

add_library(${PLUGIN}_ui SHARED
  casynth_ui_main.cxx
  ${${PLUGIN}_ui_FLTK_UI_SRCS}
)

set_target_properties(${PLUGIN} PROPERTIES PREFIX "")
set_target_properties(${PLUGIN}_ui PROPERTIES PREFIX "")

set_target_properties(${PLUGIN} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
set_target_properties(${PLUGIN}_ui PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)

target_link_libraries(${PLUGIN} ${LV2_LIBRARIES} m)
target_link_libraries(${PLUGIN}_ui ${LV2_LIBRARIES} ${NTK_LIBRARIES} ${CAIRO_LIBRARIES} m)

# config install
install(TARGETS ${PLUGIN} ${PLUGIN}_ui
  LIBRARY
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/lv2/${PLUGIN}.lv2
)

install (FILES manifest.ttl ${PLUGIN}.ttl ${PLUGIN}_presets.ttl
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/lv2/${PLUGIN}.lv2
)
