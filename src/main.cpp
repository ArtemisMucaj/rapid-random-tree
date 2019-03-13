#include "rrt.h"
#include "SDL2/SDL.h"

#define SIZE_X 640
#define SIZE_Y 400
#define MAX_POINTS 20000

int main() {
  RRT::Leaf* tree = new RRT::Leaf(SIZE_X / 2, SIZE_Y / 2);
  RRT::RRT* b = new RRT::RRT(tree);
  b->build(MAX_POINTS, SIZE_X, SIZE_Y);

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  if (SDL_CreateWindowAndRenderer(SIZE_X, SIZE_Y, 0, &window, &renderer) != 0) {
    return -1;
  }

  SDL_bool cond = SDL_FALSE;
  while (!cond) {
    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); 
    // Draw tree
    tree->draw(renderer);

    SDL_RenderPresent(renderer);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        cond = SDL_TRUE;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
