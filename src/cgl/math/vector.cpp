#include "cgl/const.hpp"
#include "cgl/math/vector.hpp"
#include "cgl/math/rotationmatrix.hpp"

#include <cmath>
#include <iostream>

namespace cgl::math {
  Vector::Vector(const Float& _x, const Float& _y, const Float& _z): x(_x), y(_y), z(_z) {}
  Vector::Vector(const Vector& other): x(other.x), y(other.y), z(other.z) {}

  Float Vector::magnitude() const {
    return std::sqrt(x*x + y*y + z*z);
  }

  void Vector::operator*=(const Float& scalar) { x *= scalar; y *= scalar; z *= scalar; }
  Vector Vector::operator*(const Float& scalar) const { return {x * scalar, y * scalar, z * scalar}; }
  void Vector::operator/=(const Float& scalar) { x /= scalar; y /= scalar; z /= scalar; }
  Vector Vector::operator/(const Float& scalar) const { return {x / scalar, y / scalar, z / scalar}; }

  void Vector::operator+=(const Vector& vector) { x += vector.x; y += vector.y; z += vector.z; }
  Vector Vector::operator+(const Vector& vector) const { return {x + vector.x, y + vector.y, z + vector.z}; }
  void Vector::operator-=(const Vector& vector) { x -= vector.x; y -= vector.y; z -= vector.z; }
  Vector Vector::operator-(const Vector& vector) const { return {x - vector.x, y - vector.y, z - vector.z}; }

  void Vector::operator*=(const RotationMatrix& rmatrix) {
    const Float _x = x, _y = y, _z = z;
    const auto& mat = rmatrix.matrix;
    x = mat[0][0] * _x + mat[0][1] * _y + mat[0][2] * _z;
    y = mat[1][0] * _x + mat[1][1] * _y + mat[1][2] * _z;
    z = mat[2][0] * _x + mat[2][1] * _y + mat[2][2] * _z;
  }

  Vector Vector::operator*(const RotationMatrix& rmatrix) const {
    const auto& mat = rmatrix.matrix;
    return {
      mat[0][0] * x + mat[0][1] * y + mat[0][2] * z,
      mat[1][0] * x + mat[1][1] * y + mat[1][2] * z,
      mat[2][0] * x + mat[2][1] * y + mat[2][2] * z
    };
  }

  void Vector::operator/=(const RotationMatrix& rmatrix) {
    const Float _x = x, _y = y, _z = z;
    const auto& mat = rmatrix.matrix;
    x = mat[0][0] * _x + mat[1][0] * _y + mat[2][0] * _z;
    y = mat[0][1] * _x + mat[1][1] * _y + mat[2][1] * _z;
    z = mat[0][2] * _x + mat[1][2] * _y + mat[2][2] * _z;
  }

  Vector Vector::operator/(const RotationMatrix& rmatrix) const {
    const auto& mat = rmatrix.matrix;
    return {
      mat[0][0] * x + mat[1][0] * y + mat[2][0] * z,
      mat[0][1] * x + mat[1][1] * y + mat[2][1] * z,
      mat[0][2] * x + mat[1][2] * y + mat[2][2] * z
    };
  }

  std::ostream& operator<<(std::ostream& stream, const Vector& vector) {
    return stream << "Vector{" << vector.x << ", " << vector.y << ", " << vector.z << "}";
  }
}
