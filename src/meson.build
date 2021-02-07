subdir('cgl')

sources = files(
  'main.cpp'
)

executable('SoftwareRenderer', sources, include_directories: [include], dependencies: [sdl2_dep], link_with: [cgl_lib])