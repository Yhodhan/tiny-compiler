#include "emitter.h"
#include <stdio.h>

Emitter init_emitter(char* full_path){
  Emitter emitter = {
    .path = NULL,
    .code = "",
    .header = "",
  };

  emitter.path = umalloc(sizeof(char) * (strlen(full_path)+1));
  strcpy(emitter.path, full_path);

  return emitter; 
}

char* concat(char* dst, char* src){
  // one additional space for ' ' and other for null character
  int total_size = strlen(dst) + strlen(src) + 2;
  char* code = umalloc(sizeof(char) * total_size);

  strcpy(code, dst);
  strcat(code, " ");
  strcat(code, src);

  return code;
}

void emit(Emitter* emitter, char* code){
  emitter->code = concat(emitter->code, code);
}

void emit_line(Emitter* emitter, char* code){
  emitter->code = concat(emitter->code, code);
  emitter->code = concat(emitter->code, "\n");
}

void header_line(Emitter* emitter, char* code){
  emitter->header = concat(emitter->header, code);
  emitter->header = concat(emitter->header, "\n");
}

void write_file(Emitter* emitter){
  char* code = concat(emitter->header, emitter->code);
  FILE* fptr = fopen(emitter->path, "w");
  fprintf(fptr, "%s",code);
  fclose(fptr);
}