#include <iostream>

#include "cgl/const.hpp"
#include "cgl/math/vector2i.hpp"

namespace cgl::math {
  std::ostream& operator<<(std::ostream& stream, const Vector2i& vector) {
    return stream << "Vector2i{ x:" << vector.x << ", y:" << vector.y << " }";
  }
}