#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Set {
  char **arr;
  int last_elem_index;
  unsigned int size;
  unsigned int capacity;
};

typedef struct Set Set;

Set init_set();
void print_set(Set *set);
void delete_set(Set *set);
void add(Set *set, char *elem);
int exists(Set *set, char *elem);

#endif
