namespace cgl::math {
  struct Vector2i;
}

#pragma once

#include "cgl/const.hpp"
#include <iostream>

struct cgl::math::Vector2i {
  Int x, y;

  friend std::ostream& operator<<(std::ostream&, const Vector2i&);
};