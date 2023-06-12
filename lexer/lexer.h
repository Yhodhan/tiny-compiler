#ifndef LEXER_H
#define LEXER_H

#include "stdlib.h"
#include "stdio.h"
#include "../token/token.h"

struct Lexer{
  char* source;
  char cur_char;
  int cur_pos;
  unsigned source_size;
};

typedef struct Lexer Lexer;

char peek(Lexer* lex);
void next_char(Lexer* lex);
void aborted(char ch);
void skip_white_space(Lexer* lex);
void skip_comment(Lexer* lex);
void delete_lex(Lexer* lex);
Token get_token(Lexer* lex);
Lexer new_lex(unsigned int size);

#endif