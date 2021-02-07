#include "cgl/const.hpp"
#include "cgl/sdl/app.hpp"
#include "cgl/color.hpp"
#include "cgl/math.hpp"
#include "cgl/sdl/renderer.hpp"

#include <SDL2/SDL.h>
#include <iostream>

namespace cgl::sdl {
  using namespace math;
  Renderer::Renderer(const App& app) : parent_app{app}, renderer(app.renderer) {}
  void Renderer::setColor(const Color& color) {
    SDL_SetRenderDrawColor(
      renderer,
      static_cast<uint8_t>(color.R * 255),
      static_cast<uint8_t>(color.G * 255),
      static_cast<uint8_t>(color.B * 255),
      static_cast<uint8_t>(color.A * 255)
    );
  }
  void Renderer::clear() {
    SDL_RenderClear(renderer);
  }
  const Vector2i& Renderer::getSize() {
    return parent_app.window_size;
  }
  void Renderer::drawPoint(const Vector& vector) {
    SDL_RenderDrawPointF(renderer, vector.x + parent_app.window_size.x / 2, vector.y + parent_app.window_size.y / 2);
  }
  void Renderer::drawLineSegment(const Vector& a, const Vector& b) {
    SDL_RenderDrawLineF(renderer, a.x + parent_app.window_size.x / 2, a.y + parent_app.window_size.y / 2, b.x + parent_app.window_size.x / 2, b.y + parent_app.window_size.y / 2);
  }

  void Renderer::finalize() {
    SDL_RenderPresent(renderer);
  }

  void Renderer::drawPixelBuffer(const PixelBuffer& pb) {
    SDL_RenderCopy(renderer, pb.to_sdl_texture(), nullptr, nullptr);
  }

}