#pragma once

#include "cgl/const.hpp"
#include "cgl/math.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <functional>

namespace cgl::sdl {
  using math::Vector2i;
  struct Renderer;
  struct App {
  public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    std::string window_name;
    Vector2i window_size;
    
    std::function<void()> tick_fn;
    std::function<void()> rasterize_fn;
    std::function<void()> draw_fn;
    std::function<void(const SDL_Event&)> event_handler;
    Float tps;
    Float fps;
    
    App(const std::string& name, const Vector2i& window_size = {640, 480});
    ~App();

    void mainloop();

    friend Renderer;
  };
}