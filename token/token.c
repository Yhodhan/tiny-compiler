#include "token.h"

int check_if_keyword(char* str) {
  if (!strcmp(str, "LABEL")) {
    return 101;
  }
  if (!strcmp(str, "GOTO")) {
    return 102;
  }
  if (!strcmp(str, "PRINT")) {
    return 103;
  }
  if (!strcmp(str, "INPUT")) {
    return 104;
  }
  if (!strcmp(str, "LET")) {
    return 105;
  }
  if (!strcmp(str, "IF")) {
    return 106;
  }
  if (!strcmp(str, "THEN")) {
    return 107;
  }
  if (!strcmp(str, "ENDIF")) {
    return 108;
  }
  if (!strcmp(str, "WHILE")) {
    return 109;
  }
  if (!strcmp(str, "REPEAT")) {
    return 110;
  }
  if (!strcmp(str, "ENDWHILE")) {
    return 111;
  }

  return 0;
}

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

  token.text = tmalloc(sizeof(char) * size+1);
  for(int i = 0; i < size; i++){
    token.text[i] = ch[i];
  }

  token.text[size] = '\0';
  token.type = type;
  return token;
}