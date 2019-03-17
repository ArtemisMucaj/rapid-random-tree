#ifndef NODE_H
#define NODE_H

#include "leaf.h"
#include <iostream>
#include "SDL2/SDL.h"

namespace RRT {

class Node {
  public:
  
  void* payload;
  Node* next;

  Node(): payload(NULL), next(NULL) {}

  Node(void* payload0, Node* next0): payload(payload0), next(next0) {}

  Node* unshift(void* val) {
    Node* tmp = new Node(val, this);
    return tmp;
  }

  void draw(SDL_Renderer* renderer) {
    Node* curr = this;
    Node* next = NULL;
    while(curr->next != NULL) {
      next = curr->next;
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
      Leaf* l1 = (Leaf*) curr->payload;
      Leaf* l2 = (Leaf*) next->payload;
      SDL_RenderDrawLine(renderer, l1->x, l1->y, l2->x, l2->y);
      curr = next;
    }
  }
};

}
#endif
