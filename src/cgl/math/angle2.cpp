#include "cgl/const.hpp"
#include "cgl/math/const.hpp"
#include "cgl/math/angle2.hpp"

namespace cgl::math {
  Angle2::Angle2(const Float& _latitude, const Float& _longitude): latitude(_latitude), longitude(_longitude) {}
  Angle2::Angle2(const Angle& _latitude, const Angle& _longitude): latitude(_latitude), longitude(_longitude) {}

  void Angle2::operator+=(const Angle2& angle) {
    latitude += angle.latitude;
    longitude += angle.longitude;
  }

  Angle2 Angle2::operator+(const Angle2& angle) const {
    return {latitude + angle.latitude, longitude + angle.longitude};
  }

  void Angle2::operator-=(const Angle2& angle) {
    latitude -= angle.latitude;
    longitude -= angle.longitude;
  }
  
  Angle2 Angle2::operator-(const Angle2& angle) const {
    return {latitude - angle.latitude, longitude - angle.longitude};
  }

  std::ostream& operator<<(std::ostream& stream, const Angle2& angle) {
    return stream << "Angle2{" << angle.latitude.value << ", " << angle.longitude.value << "}";
  }
}

