#ifndef RAPID_TREE_H
#define RAPID_TREE_H

#define DELTA 2

#include <iostream>
#include "leaf.h"
#include "node.h"

namespace RRT {

class RRT {
  int iteration;
  Leaf* tree;

  public:

  RRT(): iteration(0), tree(NULL) {}

  RRT(Leaf* t0): iteration(0), tree(t0) {}

  void build(int iter, int size_x, int size_y) {
    std::srand(time(0));
    while (iteration < iter) {
      Leaf* random = new Leaf(std::rand() % size_x, std::rand() % size_y);
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
      ++iteration;
    }
  }

  Node* path_to(int x, int y) {
    Leaf* curr = tree->closest_to(new Leaf(x, y));
    Node* path = new Node(curr, NULL);
    while (curr->parent != NULL) {
      path = path->unshift(curr->parent);
      curr = curr->parent;
    }
    return path;
  }

  static void serialize(RRT* val) {
    return;
  }

  static RRT* unserialize() {
    return new RRT();
  }
};

}
#endif
