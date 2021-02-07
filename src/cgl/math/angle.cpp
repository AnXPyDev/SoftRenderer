#include "cgl/const.hpp"
#include "cgl/math/const.hpp"
#include "cgl/math/angle.hpp"

#include <iostream>
#include <cmath>

namespace cgl::math {
  Angle::Angle(const Float& _value): value(_value) { reduce(); }
  Angle::Angle(const Angle& angle): value(angle.value) {}

  void Angle::reduce() {
    value = std::fmod(1 + std::fmod(value, 1), 1);
  }

  Float Angle::radians() const {
    return value * TAU;
  }

  void Angle::operator+=(const Float& angle) {
    value += angle;
    reduce();
  }

  Angle Angle::operator+(const Float& angle) const {
    return value + angle;
  }

  void Angle::operator-=(const Float& angle) {
    value -= angle;
    reduce();
  }

  Angle Angle::operator-(const Float& angle) const {
    return value - angle;
  }

  void Angle::operator+=(const Angle& angle) {
    value += angle.value;
    reduce();
  }

  Angle Angle::operator+(const Angle& angle) const {
    return value + angle.value;
  }

  void Angle::operator-=(const Angle& angle) {
    value -= angle.value;
    reduce();
  }

  Angle Angle::operator-(const Angle& angle) const {
    return value - angle.value;
  }

}