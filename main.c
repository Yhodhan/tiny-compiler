#include <stdio.h>
#include "lexer/lexer.h"
#include "mem_tracker/mem_tracker.h"
#include "parser/parser.h"

// calculates file size without considering last EOF character
unsigned int file_size(FILE* fptr) {
   char ch;
   unsigned int size = 0;
   do {
     ch = fgetc(fptr);
     size++;
   } while(ch != EOF);

   return size;
}

void read_file(FILE* fptr, Lexer* lex){
  char ch;
  int i = 0;
  do {
    ch = fgetc(fptr);
    lex->source[i] = ch;
    i++;
  } while(ch != EOF);

  lex->source[i-1] = '\0';
}

Lexer init_lexer(char* path) {
  // get file size
  // return pointer to file init
  FILE* fptr = fopen(path, "r+");
  unsigned int size = file_size(fptr);
  rewind(fptr);

  // create lexer and copy source code
  Lexer lex = new_lex(size);
  lex.source  = tmalloc(sizeof(char)*(size+1));  
  read_file(fptr, &lex);

  // close file descriptor
  fclose(fptr);
  return lex;
}

int main(int argc, char* argv[]){
  printf("*************************\n");
  printf("    compiler initiates   \n");
  printf("*************************\n");

  if (argc < 1){
    printf("Error: Compiler needs source file as argument");
    exit(1);
  }

  Lexer lexer = init_lexer(argv[1]);
  Parser parser = init_parser(lexer); 

  program(&parser);
  tfree();
  printf("Parsing completed\n");
    
  return 0;
}