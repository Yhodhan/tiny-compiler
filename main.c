#include "lexer/lexer.h"
#include "token/token.h"

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
  lex.source  = malloc(sizeof(char)*(size+1));  
  read_file(fptr, &lex);

  // close file descriptor
  fclose(fptr);
  return lex;
}

int main(){
  Lexer lex = init_lexer("test/case.pcc");
  Token token = get_token(&lex);
  // try lexer
  while(token.type != EOF){
    printf("token text %s \n", token.text);
    printf("token type %d \n", token.type);
    next_char(&lex);
    delete_token(token);
    token = get_token(&lex);
  };
  delete_token(token);

  delete_lex(&lex);
  return 0;
}