namespace cgl {
  struct Viewport;
}

#pragma once

#include "cgl/math.hpp"
#include "cgl/const.hpp"
#include "cgl/pixelbuffer.hpp"

namespace cgl {
  using namespace math;

  struct Viewport {
    Vector origin;
    Vector size;
    Vector scale;

    Vector toPixelBuffer(const Vector&, const PixelBuffer&);
    Triangle toPixelBuffer(const Triangle&, const PixelBuffer&);
    Viewport(const Vector& origin, const Vector& size, const Vector& scale);
  };
}