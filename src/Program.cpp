#include <Program.hpp>
#include <SDL.h>

#include <iostream>

namespace sht {

Program::Program() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Initialization Fail: " << SDL_GetError() << std::endl;
  }
}
Program::~Program() {
  SDL_Quit();
}

int Program::run() {
  std::vector<SDL_Color> const colors = {
    { 255, 0, 0, 255 },
    { 0, 255, 0, 255 },
    { 0, 0, 255, 255 },
  };
  int const wid = 640;
  int const hei = 480;
  int const refresh_time = 200;
  SDL_Window *p_window = nullptr;
  SDL_Renderer *p_renderer = nullptr;
  if (SDL_CreateWindowAndRenderer(wid, hei, 0, &p_window, &p_renderer) < 0) {
    std::cerr << "SDL_CreateWindowAndRenderer Error: " << SDL_GetError() << std::endl;
    return -1;
  }
  SDL_SetWindowTitle(p_window, "Screen flip example");

  int last_tick_count = SDL_GetTicks();
  int cur_tick_count = last_tick_count;
  int color = 0;
  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }
      }
    }
    cur_tick_count = SDL_GetTicks();
    if (cur_tick_count - last_tick_count >= refresh_time) {
      ++color %= (int)colors.size();
      SDL_SetRenderDrawColor(p_renderer,
                             colors[color].r,
                             colors[color].g,
                             colors[color].b,
                             colors[color].a);
      SDL_RenderClear(p_renderer);
      SDL_RenderFillRect(p_renderer, NULL);
      SDL_RenderPresent(p_renderer);
      last_tick_count = cur_tick_count;
    }
  }
  SDL_DestroyRenderer(p_renderer);
  SDL_DestroyWindow(p_window);
  return 0;
}

} // namespace sht
