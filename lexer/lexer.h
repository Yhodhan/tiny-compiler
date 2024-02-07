#ifndef LEXER_H
#define LEXER_H

#include "stdlib.h"
#include "stdio.h"
#include <ctype.h>
#include "../token/token.h"

struct Lexer{
  char* source;
  char cur_char;
  int cur_pos;
  int source_size;
};

typedef struct Lexer Lexer;

char peek(Lexer* lex);
void next_char(Lexer* lex);
void aborted(Lexer*lex, char* ch);
void skip_white_space(Lexer* lex);
void skip_comment(Lexer* lex);
void delete_lexer();
Token get_token(Lexer* lex);
Lexer new_lexer(unsigned int size);
char* copy_from_source(int begin, Lexer* lex); 
Lexer init_lexer(char* path); 

#endif