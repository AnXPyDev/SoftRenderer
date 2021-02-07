namespace cgl::math {
  struct Vector;
}

#pragma once

#include "cgl/const.hpp"
#include "cgl/math/rotationmatrix.hpp"

#include <iostream>

struct cgl::math::Vector {
  Float x, y, z;

  Vector(const Float& x, const Float& y, const Float& z);
  Vector(const Vector&);

  Float magnitude() const;

  void operator*=(const Float&);
  Vector operator*(const Float&) const;
  void operator/=(const Float&);
  Vector operator/(const Float&) const;

  void operator+=(const Vector&);
  Vector operator+(const Vector&) const;
  void operator-=(const Vector&);
  Vector operator-(const Vector&) const;

  void operator*=(const RotationMatrix&);
  Vector operator*(const RotationMatrix&) const;
  void operator/=(const RotationMatrix&);
  Vector operator/(const RotationMatrix&) const;

  friend std::ostream& operator<<(std::ostream&, const Vector&);
};