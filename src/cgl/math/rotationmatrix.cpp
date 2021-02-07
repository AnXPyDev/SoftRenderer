#include "cgl/const.hpp"
#include "cgl/math/const.hpp"
#include "cgl/math/angle2.hpp"
#include "cgl/math/rotationmatrix.hpp"

#include <cmath>
#include <iostream>

namespace cgl::math {
  RotationMatrix::RotationMatrix() {}
  RotationMatrix::RotationMatrix(const Angle2& angle) {
    const auto latrad = angle.latitude.radians();
    const auto lonrad = angle.longitude.radians();
    const auto latcos = std::cos(latrad);
    const auto latcos90 = std::cos(latrad + PI/2);
    const auto latsin = std::sin(latrad);
    const auto latsin90 = std::sin(latrad + PI/2);
    const auto loncos = std::cos(lonrad);
    const auto loncos90 = std::cos(lonrad + PI/2);
    const auto lonsin = std::sin(lonrad);
    const auto lonsin90 = std::sin(lonrad + PI/2);

    matrix[0][0] = latcos * loncos;
    matrix[0][1] = latcos90;
    matrix[0][2] = latcos * loncos90;
    matrix[1][0] = latsin * loncos;
    matrix[1][1] = latsin90;
    matrix[1][2] = latsin * loncos90;
    matrix[2][0] = lonsin;
    matrix[2][1] = 0;
    matrix[2][2] = lonsin90;
  }
}