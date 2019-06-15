#include <string>

#ifndef NODE_CPP
#define NODE_CPP

struct Node {
  char item;
  int priority;
  Node *left;
  Node *right;
  Node *next;
};

#endif
