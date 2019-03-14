#ifndef RAPID_TREE_H
#define RAPID_TREE_H

#define DELTA 2

#include <iostream>
#include "leaf.h"

namespace RRT {

class RRT {
  int iterations;
  Leaf* tree;

  public:

  RRT(Leaf* t0): iterations(0), tree(t0) {}

  void build(int max_iterations, int max_x, int max_y) {
    std::srand(time(0));
    while (iterations < max_iterations) {
      Leaf* random = new Leaf(std::rand() % max_x, std::rand() % max_y);
      Leaf* closest = tree->closest_to(random);
      if (*closest == *random) {
        continue;
      }
      double norm = closest->distance_to(random);
      Leaf* leaf= new Leaf(
        (closest->x + (DELTA/norm) * (random->x - closest->x)),
        (closest->y + (DELTA/norm) * (random->y - closest->y))
      );
      closest->push_back(leaf);
      ++iterations;
    }
  }
};

}
#endif
