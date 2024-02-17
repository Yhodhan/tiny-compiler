#include <stdio.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "emitter/emitter.h"

int main(int argc, char* argv[]){
  printf("*************************\n");
  printf("    compiler initiates   \n");
  printf("*************************\n");

  if (argc < 1){
    printf("Error: Compiler needs source file as argument");
    exit(EXIT_FAILURE);
  }

  Lexer lexer = init_lexer(argv[1]);
  Emitter emitter = init_emitter("emit.c");
  Parser parser = init_parser(lexer, emitter); 

  program(&parser);
  printf("Compiling completed\n");

  write_file(&parser.emitter);
     
  delete_parser(&parser);
  return 0;
}