project('SoftwareRenderer', 'cpp', default_options: ['cpp_std=c++2a'])

sdl2_lib = meson.get_compiler('cpp').find_library('SDL2')
sdl2_dep = declare_dependency(dependencies: [sdl2_lib])

include = include_directories('include')
subdir('include')
subdir('src')