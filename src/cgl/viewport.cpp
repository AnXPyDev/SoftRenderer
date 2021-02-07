#include "cgl/math.hpp"
#include "cgl/pixelbuffer.hpp"
#include "cgl/const.hpp"
#include "cgl/viewport.hpp"

namespace cgl {
  using namespace math;

  Vector Viewport::toPixelBuffer(const Vector& vector, const PixelBuffer& pb) {

    const double xm = (((vector.x - origin.x) * scale.x) + (size.x / 2)) / size.x;
    const double ym = (((vector.y - origin.y) * scale.y) + (size.y / 2)) / size.y;

    return Vector {
      xm * (double)pb.size.x, ym * (double)pb.size.y, vector.z
    };
  }

  Triangle Viewport::toPixelBuffer(const Triangle& tri, const PixelBuffer& pb) {
    return {
      toPixelBuffer(tri.vertices[0], pb),
      toPixelBuffer(tri.vertices[1], pb),
      toPixelBuffer(tri.vertices[2], pb)
    };
  }

  Viewport::Viewport(const Vector& _origin, const Vector& _size, const Vector& _scale) : origin(_origin), size(_size), scale(_scale) {}
}