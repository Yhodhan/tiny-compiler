#include "token.h"
#include <stdlib.h>

int token_text_size(char* txt) {
   int i = 0;
   while (txt[i] != '\0') {
    i++;
  } 
  return i;
}

void delete_token(Token t) {
  free(t.text);
}

Token new_token(char* ch, enum TokenType type){
  Token token;
  int size = token_text_size(ch);

  token.text = malloc(sizeof(char) * size+1);
  for(int i = 0; i < size; i++){
    token.text[i] = ch[i];
  }

  token.text[size] = '\0';
  token.type = type;
  return token;
}