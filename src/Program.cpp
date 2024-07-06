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
  SDL_Color const green = { 0, 255, 0, 255 };
  SDL_Color const purple = { 255, 0, 255, 255 };
  int const wid = 640;
  int const hei = 480;
  SDL_Window *p_window = nullptr;
  SDL_Renderer *p_renderer = nullptr;
  if (SDL_CreateWindowAndRenderer(wid, hei, 0, &p_window, &p_renderer) < 0) {
    std::cerr << "SDL_CreateWindowAndRenderer Error: " << SDL_GetError() << std::endl;
    return -1;
  }
  SDL_SetWindowTitle(p_window, "Screen flip example");
  int lastTickCount = SDL_GetTicks();
  int curTickCount = lastTickCount;
  int color = 0;
  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }
      }
    }
    curTickCount = SDL_GetTicks();
    if (curTickCount - lastTickCount > 100) {
      ++color %= 2;
      lastTickCount = curTickCount;
    }
    if (color == 0) {
      SDL_SetRenderDrawColor(
          p_renderer, green.r, green.g, green.b, green.a);
    } else {
      SDL_SetRenderDrawColor(
          p_renderer, purple.r, purple.g, purple.b, purple.a);
    }
    SDL_RenderClear(p_renderer);
    SDL_RenderFillRect(p_renderer, NULL);
    SDL_RenderPresent(p_renderer);
  }
  SDL_DestroyRenderer(p_renderer);
  SDL_DestroyWindow(p_window);
  return 0;
}

} // namespace sht
