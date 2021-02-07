#pragma once

#include <chrono>
#include <string>

namespace cgl {
  struct Timer {
    std::string_view name;
    std::chrono::time_point<std::chrono::high_resolution_clock> begin;
    Timer(std::string_view name);
    ~Timer();
  };
}