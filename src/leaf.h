#ifndef LEAF_H
#define LEAF_H

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>

#include "SDL2/SDL.h"

namespace RRT {

class Leaf {
  public:

  int x;
  int y;

  Leaf* parent;
  std::vector<Leaf*> children;


  Leaf(): x(0), y(0) {
    parent = NULL;
  }

  Leaf(int x0, int y0): x(x0), y(y0) {
    parent = NULL;
  }

  Leaf(int x0, int y0, Leaf* parent0): x(x0), y(y0), parent(parent0) {}

  std::string to_string() {
    std::ostringstream oss;
    oss << "(" << x << " ," << y << ")";
    return oss.str();
  }

  void print() {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
  }

  void draw(SDL_Renderer* renderer) {
    int size = children.size();
    for(int i = 0; i < size; i++) {
      SDL_RenderDrawLine(renderer, x, y, children[i]->x, children[i]->y);
      children[i]->draw(renderer);
    }
  }

  void draw(Leaf* dst, SDL_Renderer* renderer) {
    SDL_RenderDrawLine(renderer, x, y, dst->x, dst->y);
  }

  void push_back(int x0, int y0) {
    Leaf* child = new Leaf(x0, y0, this);
    children.push_back(child);
  }

  void push_back(Leaf* curr) {
    curr->parent = this;
    children.push_back(curr);
  }

  Leaf* closest_to(Leaf* curr) {
    Leaf *tmp = NULL, *res = this;
    int size = children.size();
    double norm = distance_to(curr->x, curr->y), norm_tmp;
    for(int i = 0; i < size; i++) {
      tmp = children[i]->closest_to(curr);
      norm_tmp = curr->distance_to(tmp);
      res = (norm_tmp < norm) ? tmp : res;
      norm = (norm_tmp < norm) ? norm_tmp : norm;
    }
    return res;
  }

  double distance_to(int x0, int y0) {
    return sqrt(
      pow(x0 - x, 2) + pow(y0 - y, 2)
    );
  }

  double distance_to(Leaf* curr) {
    return sqrt(
      pow(curr->x - x, 2) + pow(curr->y - y, 2)
    );
  }
};

}
#endif
