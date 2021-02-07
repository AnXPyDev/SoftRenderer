#include <chrono>
#include <string>
#include <iostream>

#include "cgl/timer.hpp"

namespace cgl {
  Timer::Timer(std::string_view _name) : name(_name) {
    begin = std::chrono::high_resolution_clock::now();
  }

  Timer::~Timer() {
    std::cout << "Timer " << name << ": " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin).count() << "us\n";
  }
}