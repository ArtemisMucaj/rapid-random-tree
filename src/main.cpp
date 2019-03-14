#include "rrt.h"
#include "SDL2/SDL.h"
#include <iostream>
#include <thread>
#include <chrono>

#define SIZE_X 640
#define SIZE_Y 400
#define MAX_POINTS 10000

int main() {
  RRT::Leaf* tree = new RRT::Leaf(SIZE_X / 2, SIZE_Y / 2);
  RRT::RRT* b = new RRT::RRT(tree);

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  if (SDL_CreateWindowAndRenderer(SIZE_X, SIZE_Y, 0, &window, &renderer) != 0) {
    return -1;
  }

  std::thread t1(&RRT::RRT::build, b, MAX_POINTS, SIZE_X, SIZE_Y);

  SDL_bool cond = SDL_FALSE;
  while (!cond) {
    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // Draw tree
    tree->draw(renderer);

    SDL_RenderPresent(renderer);
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        cond = SDL_TRUE;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
  }

  t1.join();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
