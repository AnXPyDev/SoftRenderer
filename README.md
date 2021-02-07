# Software Renderer

This is an incomplete project meant only for educational purposes.
I started developing this with the motivation to create a functional software renderer and learn about 3D graphics.
Although I've learned a lot about graphics and got the basics of a renderer down, I've lost motivation to continue the project.

## TODO (maybe)

Improve performance by using multithreading.
Fix rasterizeLine function to render only inside the pixelbuffer.

## Compiling

If you decide to run this, the dependencies are *a c++20 compiler*, *meson* and *SDL2*.
1. Clone this repository, *cd* into the directory.
2. *meson build --buildtype release*
3. *cd build*
4. *meson compile*