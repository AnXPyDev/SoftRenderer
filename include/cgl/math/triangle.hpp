namespace cgl::math {
  struct Triangle;
}

#pragma once

#include "cgl/const.hpp"
#include "cgl/math/vector.hpp"

struct cgl::math::Triangle {
  Vector vertices[3];
};