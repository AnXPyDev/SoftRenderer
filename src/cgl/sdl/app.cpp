#include "cgl/const.hpp"
#include "cgl/sdl/app.hpp"
#include "cgl/math.hpp"

#include <iostream>
#include <exception>
#include <functional>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <SDL2/SDL.h>

namespace cgl::sdl {
  using math::Vector2i;
  App::App(const std::string& name, const Vector2i& size): window_name(name), window_size(size), tps(0), fps(0) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      throw std::runtime_error(SDL_GetError());
    }

    window = SDL_CreateWindow(
      window_name.c_str(), 
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      window_size.x, window_size.y,
      SDL_WINDOW_SHOWN
    );

    SDL_SetRelativeMouseMode((SDL_bool)1);

    renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED
    );

    if (window == nullptr || renderer == nullptr) {
      throw std::runtime_error("SDL2: Failed create window and renderer");
    }
  }
  App::~App() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  void App::mainloop() {
    SDL_Event event;

    std::mutex render_mutex;

    bool isRunning = true;

    std::thread tick_thread(
      [&](){
        auto last = std::chrono::system_clock::now();
        while (isRunning) {
          auto current = std::chrono::system_clock::now();
          auto diff = std::chrono::duration_cast<std::chrono::microseconds>(current - last).count();
          if (1000000 / tps <= diff) {
            last = current;
            tick_fn();
          }
        }
      }
    );

    bool rasterize_inside_lock = false;
    bool rasterize_outside_lock = false;

    std::thread rasterize_thread(
      [&](){
        auto last = std::chrono::system_clock::now();
        while (isRunning) {
          auto current = std::chrono::system_clock::now();
          auto diff = std::chrono::duration_cast<std::chrono::microseconds>(current - last).count();
          if (1000000 / fps <= diff) {
            last = current;
            std::lock_guard<std::mutex> render_guard(render_mutex);
            rasterize_fn();
          }
          
        }
      }
    );

    auto last = std::chrono::system_clock::now();
    while (isRunning) {
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          isRunning = false;
        } else {
          event_handler(event);
        }
      }
      
      auto current = std::chrono::system_clock::now();
      auto diff = std::chrono::duration_cast<std::chrono::microseconds>(current - last).count();
      if (1000000 / fps <= diff && !rasterize_inside_lock) {
        last = current;
        std::lock_guard<std::mutex> render_guard(render_mutex);
        draw_fn();
      }
    }

    tick_thread.join();
    rasterize_thread.join();
  }
}

int WinMain(int argc, char** argv) {
  return main(argc, argv);
}