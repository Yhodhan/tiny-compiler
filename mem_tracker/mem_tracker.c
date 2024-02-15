#include "mem_tracker.h"

unsigned int initialized = 0;
ListTracker list;

ListTracker init() {
  ListTracker l = {
    .head = NULL,
  };

  initialized = 1;

  return l;
}

void* umalloc(unsigned int size) {
  void* alloc_mem = (void*) malloc(size);
  Node* new_node = malloc(sizeof(Node));

  if (!initialized){
    list = init();
  }

  if (list.head == NULL){
    list.head = new_node;
    list.head->next  = NULL;
    list.head->ptr = alloc_mem;
  } 
  else {
    new_node->next = list.head;
    new_node->ptr = alloc_mem;
    list.head = new_node;
  }

  return alloc_mem;
}

void ufree() {
  if (list.head == NULL) {
    return;
  }

  Node* n = list.head;
  while (n->next != NULL){
    Node* temp = n->next;
    free(n->ptr);
    free(n);
    n = temp;
  }

  free(n->ptr);
  free(n);

  initialized = 0;
}
