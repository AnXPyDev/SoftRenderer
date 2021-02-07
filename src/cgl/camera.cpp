#include "cgl/const.hpp"
#include "cgl/camera.hpp"
#include "cgl/math.hpp"

#include <cmath>
#include <iostream>

using namespace cgl;

namespace cgl {
  using namespace math;
  Camera::Camera(const Vector& origin, const Angle2& direction, Float distance) : origin(origin), direction(direction), distance(distance) {
    cache_rotm = RotationMatrix(direction);
  }

  void Camera::update() {
    cache_rotm = RotationMatrix(direction);
  }

  Vector Camera::perspectiveProjection(const Vector& vector) const {
    auto norm = vector - origin;
    auto rotated = norm / cache_rotm;
    Float mult;
    if (rotated.x == 0) {
      mult = 1;
    } else if (rotated.x > 0) {
      mult = distance / rotated.x;
    } else {
      mult = -distance / rotated.x;
    }

    return {
      -rotated.y * mult, -rotated.z * mult, rotated.x
    };

  }

  Triangle Camera::perspectiveProjection(const Triangle& tri) const {
    return {
      perspectiveProjection(tri.vertices[0]),
      perspectiveProjection(tri.vertices[1]),
      perspectiveProjection(tri.vertices[2])
    };
  }

  std::ostream& operator<<(std::ostream& stream, const Camera& camera) {
    return stream << "Camera{ " << "origin:" << camera.origin << " direction:" << camera.direction << " distance:" << camera.distance << " }";
  }
}