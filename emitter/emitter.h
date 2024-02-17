#ifndef EMITTER_H
#define EMITTER_H

#include <stdlib.h>
#include <string.h>
#include "../mem_tracker/mem_tracker.h"

struct Emitter {
  char* path;
  char* header;
  char* code;
};

typedef struct Emitter Emitter;

Emitter init_emitter(char* full_path);
void emit(Emitter* emitter, char* code);
void emit_line(Emitter* emitter, char* code);
void header_line(Emitter* emitter, char* code);
void write_file(Emitter* emitter);
char* concat(char* dst, char* src);

#endif
