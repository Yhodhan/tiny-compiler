#include "token.h"
#include <string.h>

struct Keyword keyword [] = {
	// Keywords.,
	{"LABEL", 101},
	{"GOTO", 102},
	{"PRINT", 103},
	{"INPUT", 104},
	{"LET", 105},
	{"IF", 106},
	{"THEN", 107},
	{"ENDIF", 108},
	{"WHILE", 109},
	{"REPEAT", 110},
	{"ENDWHILE", 111},
};

int check_if_keyword(char* str) {
  for(int i = 0; i < 26; i++) {
    if (!strcmp(str, keyword[i].label)) {
      return keyword[i].type;
    }
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

  token.text = malloc(sizeof(char) * size+1);
  for(int i = 0; i < size; i++){
    token.text[i] = ch[i];
  }

  token.text[size] = '\0';
  token.type = type;
  return token;
}