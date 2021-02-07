namespace cgl::math {
  struct Angle;
}

#pragma once

#include "cgl/const.hpp"

#include<iostream>

struct cgl::math::Angle {
  Float value;
  
  Angle(const Float&);
  Angle(const Angle&);
  void reduce();

  Float radians() const;

  void operator+=(const Float&);
  Angle operator+(const Float&) const;
  void operator-=(const Float&);
  Angle operator-(const Float&) const;

  void operator+=(const Angle&);
  Angle operator+(const Angle&) const;
  void operator-=(const Angle&);
  Angle operator-(const Angle&) const;

  friend std::ostream& operator<<(std::ostream&, Angle&);
};