#pragma once

#include "cgl/const.hpp"
#include "cgl/math.hpp"

#include <iostream>

namespace cgl {
  using namespace math;
  
  struct Camera {
    Vector origin;
    Angle2 direction;
    Float distance;
    RotationMatrix cache_rotm;
    RotationMatrix cache_inverse_rotm;

    void update();
    Camera(const Vector& origin, const Angle2& direction, Float distance);

    // Translate Vector to a plane from the perspective of the camera
    Vector perspectiveProjection(const Vector&) const;
    Triangle perspectiveProjection(const Triangle&) const;
  };

  std::ostream& operator<<(std::ostream&, const Camera&);
}