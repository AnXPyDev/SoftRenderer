namespace cgl::math {
  struct RotationMatrix;
}

#pragma once

#include "cgl/const.hpp"
#include "cgl/math/angle2.hpp"

struct cgl::math::RotationMatrix {
  Float matrix[3][3];
  
  RotationMatrix();
  RotationMatrix(const Angle2&);
};