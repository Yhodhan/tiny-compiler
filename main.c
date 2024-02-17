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
  Emitter emitter = init_emitter("test.file");
  Parser parser = init_parser(lexer); 

  program(&parser);
  printf("Parsing completed\n");
      
  delete_parser(&parser);
  return 0;
}