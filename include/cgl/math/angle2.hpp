namespace cgl::math {
  struct Angle2;
}

#pragma once

#include "cgl/const.hpp"
#include "cgl/math/angle.hpp"

#include<iostream>

struct cgl::math::Angle2 {
  Angle latitude, longitude;
  
  Angle2(const Float& latitude, const Float& longitude);
  Angle2(const Angle& latitude, const Angle& longitude);

  void operator+=(const Float&);
  Angle2 operator+(const Float&) const;
  void operator-=(const Float&);
  Angle2 operator-(const Float&) const;

  void operator+=(const Angle2&);
  Angle2 operator+(const Angle2&) const;
  void operator-=(const Angle2&);
  Angle2 operator-(const Angle2&) const;

  friend std::ostream& operator<<(std::ostream&, const Angle2&);
};