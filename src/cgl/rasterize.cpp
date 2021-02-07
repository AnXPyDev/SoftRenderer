#include "cgl/const.hpp"
#include "cgl/math.hpp"
#include "cgl/rasterize.hpp"
#include <cmath>
#include <future>

namespace cgl {
  using namespace math;

  Float clamp(Float x, Float min, Float max) {
    if (x < min) {
      return min;
    } else if (x > max) {
      return max;
    } else {
      return x;
    }
  }

  inline Float min(Float x, Float y, Float z) {
    return (x < y ? (x < z ? x : z) : (y < z ? y : z));
  }

  inline Float max(Float x, Float y, Float z) {
    return (x > y ? (x > z ? x : z) : (y > z ? y : z));
  }

  void rasterizeLine(const Vector& a, const Vector& b, const Color& color, PixelBuffer& pb) {
    const Vector dist = {
      b.x - a.x, b.y - a.y, b.z - a.z
    };


    if (std::abs(dist.x) >= std::abs(dist.y)) {
      if (a.x < b.x) {
        for (Float cx = 0; cx < dist.x; cx += 1) {
          Float ax = a.x + cx;
          Float ay = a.y + dist.y * (cx / dist.x);
          Float az = a.z + dist.z * (cx / dist.x);
          pb.setPoint({static_cast<Int>(std::floor(ax)), static_cast<Int>(std::floor(ay))}, {color, az});
        }
      } else if (a.x > b.x) {
        for (Float cx = 0; cx > dist.x; cx -= 1) {
          Float ax = a.x + cx;
          Float ay = a.y + dist.y * (cx / dist.x);
          Float az = a.z + dist.z * (cx / dist.x);
          pb.setPoint({static_cast<Int>(std::floor(ax)), static_cast<Int>(std::floor(ay))}, {color, az});
        }
      }
    } else {
      if (a.y < b.y) {
        for (Float cy = 0; cy < dist.y; cy += 1) {
          Float ax = a.x + dist.x * (cy / dist.y);
          Float ay = a.y + cy;
          Float az = a.z + dist.z * (cy / dist.y);
          pb.setPoint({static_cast<Int>(std::floor(ax)), static_cast<Int>(std::floor(ay))}, {color, az});
        }
      } else if (a.y > b.y) {
        for (Float cy = 0; cy > dist.y; cy -= 1) {
          Float ax = a.x + dist.x * (cy / dist.y);
          Float ay = a.y + cy;
          Float az = a.z + dist.z * (cy / dist.y);
          pb.setPoint({static_cast<Int>(std::floor(ax)), static_cast<Int>(std::floor(ay))}, {color, az});
        }
      }
    }
  }

  inline const Vector& maxy(const Vector& a, const Vector& b, const Vector& c) {
    return (a.y > b.y ? (a.y > c.y ? a : c) : (b.y > c.y ? b : c));
  }

  inline const Vector& miny(const Vector& a, const Vector& b, const Vector& c) {
    return (a.y < b.y ? (a.y < c.y ? a : c) : (b.y < c.y ? b : c));
  }

  void rasterizeTriangle(const Triangle& tri, const Color& color, PixelBuffer& pb) {
    const Vector (&verts)[3] = tri.vertices;


    rasterizeLine(verts[0], verts[1], color, pb);
    rasterizeLine(verts[1], verts[2], color, pb);
    rasterizeLine(verts[2], verts[0], color, pb);

    const Vector& top = miny(verts[0], verts[1], verts[2]);
    const Vector& bottom = maxy(verts[0], verts[1], verts[2]);

    const Vector* middle_ptr = nullptr;

    for (int i = 0; i < 3; i++) {
      if (&verts[i] != &top && &verts[i] != &bottom) {
        middle_ptr = &verts[i];
      }
    }

    const Vector& middle = *middle_ptr;
    const Float middle_mult = (middle.y - top.y) / (bottom.y - top.y);
    const Vector middle_opposite = {
      top.x + middle_mult * (bottom.x - top.x), middle.y, top.z + middle_mult * (bottom.z - top.z)
    };

    auto upper_future = std::async([&]() {
      const Float ydist = middle.y - top.y;
      for (Float cy = 0; cy < ydist; cy += 1) {
        const Float mult = cy / ydist;
        const Float ay = cy + top.y;
        const Float ax = top.x + (middle.x - top.x) * mult;
        const Float bx = top.x + (middle_opposite.x - top.x) * mult;
        const Float az = top.z + (middle.z - top.z) * mult;
        const Float bz = top.z + (middle_opposite.z - top.z) * mult;
        rasterizeLine({ax, ay, az}, {bx, ay, bz}, color, pb); 
      }
    });

    auto lower_future = std::async([&]() {
      const Float ydist = bottom.y - middle.y;
      for (Float cy = 0; cy < ydist; cy += 1) {
        const Float mult = cy / ydist;
        const Float ay = cy + middle.y;
        const Float ax = middle.x + (bottom.x - middle.x) * mult;
        const Float bx = middle_opposite.x + (bottom.x - middle_opposite.x) * mult;
        const Float az = middle.z + (bottom.z - middle.z) * mult;
        const Float bz =  middle_opposite.z + (bottom.z - middle_opposite.z) * mult;
        rasterizeLine({ax, ay, az}, {bx, ay, bz}, color, pb);
      }
    });
  }
}
