#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>
#include <chrono>
#include <string>

#include "cgl.hpp"

using namespace cgl;
using namespace cgl::math;

Angle lerp(Angle x, Angle y, Float m) {
  Float diff = y.value - x.value;
  if (y.value - x.value > 0.5) {
    return {x.value - (1 - diff) * m};
  } else {
    return {std::lerp(x.value, y.value, m)};
  }
}

int main(int argc, char** argv) {
  sdl::App app("cgl test", {800, 400});
  sdl::Renderer ctx(app);

  std::vector<std::tuple<Color, Vector, Vector>> lines;
  /* lines.push_back(std::make_tuple(Color({1, 0, 0, 1}), Vector({0, 0, 0}), Vector({100, 0, 0})));
  lines.push_back(std::make_tuple(Color({0, 1, 0, 1}), Vector({0, 0, 0}), Vector({0, 100, 0})));
  lines.push_back(std::make_tuple(Color({0, 0, 1, 1}), Vector({0, 0, 0}), Vector({0, 0, 100}))); */

  /* lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, 100, 100}), Vector({100, 100, 100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, 100, -100}), Vector({100,  100, -100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, -100, 100}), Vector({100, -100, 100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, -100, -100}), Vector({100,  -100, -100})));

  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({100, -100, 100}), Vector({100, 100, 100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({100, -100, -100}), Vector({100, 100, -100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, -100, 100}), Vector({-100, 100, 100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, -100, -100}), Vector({-100, 100, -100})));

  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({100, 100, -100}), Vector({100, 100, 100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({100, -100, -100}), Vector({100, -100, 100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, 100, -100}), Vector({-100, 100, 100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, -100, -100}), Vector({-100, -100, 100}))); */

/*   lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, -100, -100}), Vector({100, 100, 100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({100, -100, -100}), Vector({-100, 100, 100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({-100, -100, 100}), Vector({100, 100, -100})));
  lines.push_back(std::make_tuple(Color({1, 1, 1, 1}), Vector({100, -100, 100}), Vector({-100, 100, -100}))); */

  std::vector<std::tuple<Color, Triangle>> tris;
  
  tris.push_back(std::make_tuple(Color({1, 0, 1, 1}), Triangle({{-100, 100, -100}, {-100, 100, 100}, {-100, -100, 100}})));
  tris.push_back(std::make_tuple(Color({1, 1, 0, 1}), Triangle({{-100, 100, -100}, {-100, -100, -100}, {-100, -100, 100}})));
  tris.push_back(std::make_tuple(Color({0, 1, 1, 1}), Triangle({{100, 100, -100}, {100, 100, 100}, {100, -100, 100}})));
  tris.push_back(std::make_tuple(Color({1, 0, 1, 1}), Triangle({{100, 100, -100}, {100, -100, -100}, {100, -100, 100}})));

  tris.push_back(std::make_tuple(Color({1, 0, 0, 1}), Triangle({{-100, -100, -100}, {-100, -100, 100}, {100, -100, 100}})));
  tris.push_back(std::make_tuple(Color({0, 1, 0, 1}), Triangle({{-100, -100, -100}, {100, -100, -100}, {100, -100, 100}})));
  tris.push_back(std::make_tuple(Color({0, 0, 1, 1}), Triangle({{-100, 100, -100}, {-100, 100, 100}, {100, 100, 100}})));
  tris.push_back(std::make_tuple(Color({1, 0, 0, 1}), Triangle({{-100, 100, -100}, {100, 100, -100}, {100, 100, 100}})));

  tris.push_back(std::make_tuple(Color({0, 1, 0, 1}), Triangle({{-100, -100, -100}, {-100, 100, -100}, {100, 100, -100}})));
  tris.push_back(std::make_tuple(Color({1, 1, 0, 1}), Triangle({{-100, -100, -100}, {100, -100, -100}, {100, 100, -100}})));
  tris.push_back(std::make_tuple(Color({0, 1, 1, 1}), Triangle({{-100, -100, 100}, {-100, 100, 100}, {100, 100, 100}})));
  tris.push_back(std::make_tuple(Color({0, 1, 0, 1}), Triangle({{-100, -100, 100}, {100, -100, 100}, {100, 100, 100}})));

  Camera cam({-10000,0,0}, {Angle(0), Angle(0)}, 0);

  app.fps = 60;
  app.tps = 60;


  Vector campos = {-5000, 0, 0};
  Angle2 camrot = {0,0};
  Float camdist = 200;

  app.event_handler = [&](const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_w) {
        campos.z += 50;
      } else if (event.key.keysym.sym == SDLK_s) {
        campos.z -= 50;
      } else if (event.key.keysym.sym == SDLK_q) {
        campos.y += 50;
      } else if (event.key.keysym.sym == SDLK_a) {
        campos.y -= 50;
      } else if (event.key.keysym.sym == SDLK_e) {
        campos.x += 50;
      } else if (event.key.keysym.sym == SDLK_d) {
        campos.x -= 50;
      } else if (event.key.keysym.sym == SDLK_r) {
        camdist += 20;
      } else if (event.key.keysym.sym == SDLK_f) {
        camdist -= 20;
      } else if (event.key.keysym.sym == SDLK_UP) {
        camrot.longitude += 0.05;
      } else if (event.key.keysym.sym == SDLK_DOWN) {
        camrot.longitude -= 0.05;
      } else if (event.key.keysym.sym == SDLK_LEFT) {
        camrot.latitude += 0.05;
      } else if (event.key.keysym.sym == SDLK_RIGHT) {
        camrot.latitude -= 0.05;
      }
      std::cout << cam.origin << " " << cam.direction << " " << cam.distance << std::endl;
    } else if (event.type == SDL_MOUSEMOTION) {
      cam.direction.latitude -= (0.001 / (cam.distance / 200)) * (Float)event.motion.xrel;
      cam.direction.longitude -= (0.001 / (cam.distance / 200)) * (Float)event.motion.yrel;
      cam.update();
    }
  };


  app.tick_fn = [&]() {
    Timer timer("tick");
    const Float ls = 0.5;
    cam.origin.x = std::lerp(cam.origin.x, campos.x, ls);
    cam.origin.y = std::lerp(cam.origin.y, campos.y, ls);
    cam.origin.z = std::lerp(cam.origin.z, campos.z, ls);
    cam.distance = std::lerp(cam.distance, camdist, ls);
    //cam.direction.latitude = lerp(cam.direction.latitude, camrot.latitude, ls);
    //cam.direction.longitude = lerp(cam.direction.longitude, camrot.longitude, ls);
  };

  app.tick_fn();
  
  PixelBuffer pixelbuffer = {app, {200,100}};
  Viewport viewport = {Vector({0, 0, 0}), Vector({800, 400, 0}), Vector({1, 1, 0})};

  app.rasterize_fn = [&]() {
    Timer timer("rasterize");
    pixelbuffer.clear();

    for (int x = 0; x <= 1; x++) {
      for (int y = 0; y <= 1; y++) {
        for (int z = 0; z <= 0; z++) {
          for (const auto& tup : tris) {
            Vector offset = {x * 300, y * 300, z * 300};
            const Triangle& otri = std::get<1>(tup);
            Triangle tri = {
              otri.vertices[0] + offset,
              otri.vertices[1] + offset,
              otri.vertices[2] + offset,
            };
            rasterizeTriangle(
              viewport.toPixelBuffer(cam.perspectiveProjection(tri), pixelbuffer),
              std::get<0>(tup),
              pixelbuffer
            );
          }
        }
      }
    }

  };
  

  app.draw_fn = [&]() {
    Timer timer("draw");

    ctx.setColor({0, 0, 0, 1});
    ctx.clear();
    ctx.drawPixelBuffer(pixelbuffer);
    ctx.finalize();
    
  };

  app.mainloop();

  std::cout << std::flush;

  return 0;
}