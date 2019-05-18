project('octolo', 'c')

subdir('tikloo')

lv2_dep = dependency('lv2', version : '>=1.14.0')

install_dir = join_paths(get_option('libdir'), 'lv2', meson.project_name()+'.lv2')

shared_library(
    'octolo',
    ['octolo.c'], 
    name_prefix : '',
    link_args : '-lm',
    install : true,
    install_dir : install_dir,
    )

install_data(
    ['manifest.ttl',
     'octolo.ttl',
     'octolo_presets.ttl'
     ],
    install_dir : install_dir,
    )

shared_library(
    'octolo_ui',
    ['octolo_ui.c'],
    name_prefix : '',
    link_with : tikloo,
    link_args : '-lm',
    dependencies : tk_deps,
    install : true,
    install_dir : install_dir,
    )
