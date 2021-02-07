#include "cgl/color.hpp"
#include <iostream>

namespace cgl {
  std::ostream& operator<<(std::ostream& stream, const Color& color) {
    return stream << "Color{ R:" << color.R << " ,G:" << color.G << " ,B:" << color.B << " ,A:" << color.A << " }";
  }
}