cgl_sources = files(
  'camera.cpp',
  'sdl/app.cpp',
  'sdl/renderer.cpp',
  'math/vector.cpp',
  'math/angle.cpp',
  'math/angle2.cpp',
  'math/rotationmatrix.cpp',
  'pixelbuffer.cpp',
  'color.cpp',
  'math/vector2i.cpp',
  'rasterize.cpp',
  'timer.cpp',
  'viewport.cpp'
)

cgl_lib = static_library('cgl', cgl_sources, include_directories: include, dependencies: [sdl2_dep])