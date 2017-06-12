#cmake file to include tikloo with your project
cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig)
pkg_check_modules(CAIRO cairo REQUIRED)
pkg_check_modules(FREETYPE freetype2 REQUIRED)
#pkg_check_modules(SND sndfile )

list(APPEND TIKLOO_INCLUDE_DIRS ${CAIRO_INCLUDE_DIRS}  ${FREETYPE_INCLUDE_DIRS} tikloo ) #note this extra reference to tikloo is for the parent dir, not here
list(APPEND TIKLOO_LDFLAGS ${CAIRO_LDFLAGS} ${FREETYPE_LDFLAGS} -lm)

#platform specific libs
pkg_check_modules(X11 x11)
pkg_check_modules(USER32 user32)
pkg_check_modules(COCOA Cocoa)


add_definitions( "-DPUGL_HAVE_CAIRO" )

if(X11_FOUND)
    list(APPEND PUGL_SRC pugl/pugl_x11.c )
    list(APPEND TIKLOO_INCLUDE_DIRS ${X11_INCLUDE_DIRS} )
    list(APPEND TIKLOO_LDFLAGS ${X11_LDFLAGS} )
elseif(USER32_FOUND)
    pkg_check_modules(OPENGL32 opengl32 REQUIRED )
    pkg_check_modules(GLU32 glu32 REQUIRED )
    pkg_check_modules(GDI32 gdi32 REQUIRED )
    list(APPEND PUGL_SRC pugl/pugl_win.cpp ) 
    list(APPEND TIKLOO_INCLUDE_DIRS ${USER32_INCLUDE_DIRS} ${OPENGL32_INCLUDE_DIRS} ${GLU32_INCLUDE_DIRS} ${GDI32_INCLUDE_DIRS} )
    list(APPEND TIKLOO_LDFLAGS ${USER32_LDFLAGS} ${OPENGL32_LDFLAGS} ${GLU32_LDFLAGS} ${GDI32_LDFLAGS} )
elseif(COCOA_FOUND)
    pkg_check_modules(OPENGL OpenGL REQUIRED )
    list(APPEND PUGL_SRC pugl/pugl_osx.m )  
    list(APPEND TIKLOO_INCLUDE_DIRS ${COCOA32_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} )
    list(APPEND TIKLOO_LDFLAGS ${COCOA32_LDFLAGS} ${OPENGL_LDFLAGS} )
else()
    message(SEND_ERROR "NO APPROPRIATE UI LIBRARY FOUND (x11, cocoa, nor user32)")

endif()

#embed fonts (taken from https://github.com/rkitover/bin2c)
#note that if you change the font file you must remove the generated .h
#to regenerate it
add_executable(bin2c bin2c.c) 
file(GLOB FONTS "${CMAKE_CURRENT_SOURCE_DIR}/fonts/*.*")
foreach(FONT ${FONTS})
    get_filename_component(FFNAME ${FONT} NAME_WE)
    get_filename_component(FFEXT ${FONT} EXT)
    string(REPLACE "-" "_" VARNAME ${FFNAME})
    if(NOT ${FFEXT} MATCHES ".h") 
        if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/fonts/${VARNAME}.h)
            message("-- Preping ${FFNAME}${FFEXT} for bin2c")
            list(APPEND FONTCFILES ${VARNAME}.h)
            add_custom_command(OUTPUT ${VARNAME}.h
                COMMAND bin2c ${FONT} ${CMAKE_CURRENT_SOURCE_DIR}/fonts/${VARNAME}.h ${VARNAME}
                COMMENT "Converting ${FFNAME}${FFEXT} to header"
                DEPENDS bin2c
            )
        endif()
    else() 
        list(APPEND FONTCFILES ${VARNAME}.h)
    endif()
endforeach()

set_source_files_properties(${FONTCFILES} PROPERTIES GENERATED TRUE)

#finally the main library
set(TIKLOO_INCLUDE_DIRS ${TIKLOO_INCLUDE_DIRS} PARENT_SCOPE)
set(TIKLOO_LDFLAGS ${TIKLOO_LDFLAGS} PARENT_SCOPE)

include_directories( ${TIKLOO_INCLUDE_DIRS} ../tikloo pugl )

list(APPEND DEFAULT_DRAW_SRC
    default_draw/draw_bg.c
    default_draw/draw_blackLEDbutton.c
    default_draw/draw_dial.c
    default_draw/draw_text.c
)

add_library(tikloo STATIC 
    tk_main.c
    timer.c
    ${DEFAULT_DRAW_SRC}
    ${PUGL_SRC}
    ${FONTCFILES}
) 
