#ifndef TRACKER_H
#define TRACKER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct ListTracker ListTracker;
typedef struct Node Node;

struct Node {
  void* ptr;
  Node* next;
};

struct ListTracker {
  Node* head;
};

void* tmalloc(unsigned int size); 
void tfree();

#endif