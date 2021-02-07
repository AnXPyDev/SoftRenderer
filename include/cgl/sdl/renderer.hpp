#pragma once

#include "cgl/const.hpp"
#include "cgl/sdl/app.hpp"
#include "cgl/color.hpp"
#include "cgl/math.hpp"
#include "cgl/pixelbuffer.hpp"

#include <SDL2/SDL.h>
#include <iostream>

namespace cgl::sdl {
  using namespace math;
  struct Renderer {
  private:
    const App& parent_app;
    SDL_Renderer* renderer;
  public:
    Renderer(const App& app);
    void setColor(const Color& color);
    const Vector2i& getSize();
    void clear();
    void drawPoint(const Vector& vector);
    void drawLineSegment(const Vector& a, const Vector& b);
    void finalize();
    void drawPixelBuffer(const PixelBuffer& pb);
  };
}