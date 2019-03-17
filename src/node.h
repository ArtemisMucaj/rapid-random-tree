#ifndef NODE_H
#define NODE_H

#include "leaf.h"
#include <iostream>
#include "SDL2/SDL.h"

namespace RRT {

class Node {
  public:
  
  Leaf* val;
  Node* next;

  Node(): val(NULL), next(NULL) {}

  Node(Leaf* val0, Node* next0): val(val0), next(next0) {}

  Node* unshift(Leaf* val) {
    Node* tmp = new Node(val, this);
    return tmp;
  }

  void draw(SDL_Renderer* renderer) {
    Node* curr = this;
    Node* next = NULL;
    while(curr->next != NULL) {
      next = curr->next;
      Leaf* l1 = curr->val;
      Leaf* l2 = next->val;
      curr = next;
      // Draw
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(renderer, l1->x, l1->y, l2->x, l2->y);
    }
  }
};

}
#endif
