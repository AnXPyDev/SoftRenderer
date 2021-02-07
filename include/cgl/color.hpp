namespace cgl {
  struct Color;
}

#pragma once

#include "cgl/const.hpp"

#include <iostream>

namespace cgl {
  struct Color {
    Float R, G, B, A;

    friend std::ostream& operator<<(std::ostream&, const Color&);
  };
}