#include <stdio.h>
#include "lexer/lexer.h"
#include "mem_tracker/mem_tracker.h"
#include "parser/parser.h"


int main(int argc, char* argv[]){
  printf("*************************\n");
  printf("    compiler initiates   \n");
  printf("*************************\n");

  if (argc < 1){
    printf("Error: Compiler needs source file as argument");
    exit(EXIT_FAILURE);
  }

  Lexer lexer = init_lexer(argv[1]);
  Parser parser = init_parser(lexer); 

  program(&parser);
  tfree();
  printf("Parsing completed\n");
    
  return 0;
}