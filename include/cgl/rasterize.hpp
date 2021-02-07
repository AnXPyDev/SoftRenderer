#pragma once

#include "cgl/const.hpp"
#include "cgl/math.hpp"
#include "cgl/color.hpp"
#include "cgl/pixelbuffer.hpp"
#include "cgl/math/triangle.hpp"

namespace cgl {
  using namespace math;

  void rasterizeLine(const Vector&, const Vector&, const Color&, PixelBuffer&);
  void rasterizeTriangle(const Triangle&, const Color&, PixelBuffer&);
}