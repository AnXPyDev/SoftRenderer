#include <SDL2/SDL.h>
#include "cgl/const.hpp"
#include "cgl/math.hpp"
#include "cgl/pixelbuffer.hpp"
#include "cgl/sdl/app.hpp"
#include "cgl/timer.hpp"

#include <iostream>
#include <future>
#include <vector>

namespace cgl {
  using namespace math;

  PixelBuffer::PixelBuffer(const sdl::App& _app, const Vector2i& _size) : app(_app), texture(nullptr) {
    pixelformat.format = SDL_PIXELFORMAT_RGB888;
    setSize(_size);
    clear();
  }

  PixelBuffer::~PixelBuffer() {
    SDL_DestroyTexture(texture);
  }

  void PixelBuffer::setSize(const Vector2i& _size) {
    if (texture) {
      SDL_DestroyTexture(texture);
    }
    size = _size;
    //surface = SDL_CreateRGBSurface(0, size.x, size.y, 32, 0, 0, 0, 0);
    texture = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, size.x, size.y);
    buffer.reserve(size.x * size.y);
  }

  void PixelBuffer::clear() {
    for (Int x = 0; x < size.x; ++x) {
      for (Int y = 0; y < size.y; ++y) {
        (*this)({x, y}) = {{0, 0, 0, 1}, -1};
      }
    }
  }



  SDL_Texture* PixelBuffer::to_sdl_texture() const {
    SDL_Surface* surface;
    SDL_LockTextureToSurface(texture, nullptr, &surface);
    
    Uint32 *pixels = reinterpret_cast<Uint32*>(surface->pixels);

    const Int chunk_count = 5;
    const Int chunk_height = size.y / chunk_count;

    const auto render_chunk = [&](Int ybegin, Int yend) {
      for (Int y = ybegin; y < yend; y++) {
        for (Int x = 0; x < size.x; x++) {
          const Color& c = buffer[y * size.x + x].color;
          pixels[y * size.x + x] = SDL_MapRGB(surface->format, (Uint8)(c.R * 255), (Uint8)(c.G * 255), (Uint8)(c.B * 255));
        }
      }
    };

    {
      Timer timer("async translation");

      std::vector<std::future<void>> futures;
      futures.reserve(chunk_count);
      for (Int chunk_i = 0; chunk_i < chunk_count - 1; chunk_i++) {
        futures.push_back(std::async(render_chunk, chunk_i * chunk_height, (chunk_i + 1) * chunk_height));
      }
      futures.push_back(std::async(render_chunk, (chunk_count - 1) * chunk_height, size.y));
    }

    Timer uttimer("unlock_texture");
    SDL_UnlockTexture(texture);
    return texture;
  }

  PixelBuffer::Point& PixelBuffer::operator()(const Vector2i& index) {
    return buffer[index.y * size.x + index.x];
  }

  void PixelBuffer::setPoint(const Vector2i& index, const PixelBuffer::Point& point) {
    auto& lpoint = buffer[index.y * size.x + index.x];
    if (index.x < 0 || index.x >= size.x || index.y < 0 || index.y >= size.y) {
      return;
    }
    if ((point.depth <= lpoint.depth || lpoint.depth < 0) && point.depth >= 0) {
      buffer[index.y * size.x + index.x] = point;
    }
  }

  std::ostream& operator<<(std::ostream& stream, const PixelBuffer::Point& point) {
    return stream << "Point{ " << point.color << ", depth:" << point.depth << " }";
  }

  std::ostream& operator<<(std::ostream& stream, const PixelBuffer& pb) {
    return stream << "PixelBuffer{ size:" << pb.size << " }";
  }

}