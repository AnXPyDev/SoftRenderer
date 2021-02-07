namespace cgl {
  struct PixelBuffer;
  //struct PixelBuffer::Point;
}

#pragma once

#include <SDL2/SDL.h>
#include "cgl/const.hpp"
#include "cgl/color.hpp"
#include "cgl/math.hpp"
#include "cgl/sdl/app.hpp"

#include <vector>
#include <iostream>

namespace cgl {
  using namespace math;
  struct PixelBuffer {
    struct Point {
      Color color; Float depth;
      friend std::ostream& operator<<(std::ostream&, const Point& point);
    };

    const sdl::App& app;
    SDL_PixelFormat pixelformat;
    mutable SDL_Texture* texture;
    SDL_Surface* surface;
    
    Vector2i size;
    std::vector<Point> buffer;
    
    PixelBuffer(const sdl::App& app, const Vector2i& size);
    ~PixelBuffer();

    void clear();
    SDL_Texture* to_sdl_texture() const;
    void setSize(const Vector2i& size);
    void setPoint(const Vector2i& index, const Point& point);
    Point& operator()(const Vector2i& index);
    friend std::ostream& operator<<(std::ostream&, const PixelBuffer&);
  };
}