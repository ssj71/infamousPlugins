

# tk_include = include_directories( ) # cairo freetype, x11/user32/cocoa+friends,

cairodep = dependency('cairo')
ftdep = dependency('freetype2')
harfdep = dependency('harfbuzz')

if target_machine.system() == 'linux'
    pugldep = dependency('x11')
    puglsrc = 'pugl/pugl_x11.c'
    
elif target_machine.system() == 'darwin'
    pugldep = [dependency('Cocoa'),
               dependency('OpenGL')
              ]
    puglsrc = 'pugl/pugl_osx.m'

elif target_machine.system() == 'windows'
    pugldep = [dependency('user32'),
               dependency('opengl32'),
               dependency('glu32'),
               dependency('gdi32')
              ]
    puglsrc = 'pugl/pugl_win.cpp'

endif

tk_deps = [cairodep, ftdep, harfdep]
tk_deps += pugldep

inc = include_directories( 'pugl' )

bin2c = executable( 'bin2c', 'bin2c.c' )

fontcfiles = ['fonts/LibraSerifModern_Regular.h'] 
foreach f : [] # 'fonts/LibraSerifModern-Regular.otf'] #add your font paths here! # TODO: make it glob and convert fonts automagically
    varname = (((f.split('/')[-1]).split('.')[0]).underscorify())
    fontcfiles += custom_target( 'fonts',
                                 input : f,
                                 output : varname+'.h',
                                 command : [bin2c, '@INPUT@', '@OUTPUT@', varname]
                                 )
endforeach

sources = [ 'tk_main.c', 'timer.c',
    'default_draw/draw_bg.c',
    'default_draw/draw_blackLEDbutton.c',
    'default_draw/draw_dial.c',
    'default_draw/draw_text.c',
    puglsrc,
    fontcfiles
    ]
tikloo = static_library( 'tikloo', sources, 
                          include_directories : inc,
                          dependencies : tk_deps,
                          c_args : '-DPUGL_HAVE_CAIRO',
                          link_args : '-lm'
                          )
