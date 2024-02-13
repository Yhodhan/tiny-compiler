#ifndef LEXER_H
#define LEXER_H

#include "stdlib.h"
#include "stdio.h"
#include <ctype.h>
#include "../token/token.h"
#include "../set/set.h"

struct Lexer{
  char* source;
  char cur_char;
  int cur_pos;
  int source_size;
  Set symbols;
  Set LabelsDeclared;
  Set LabelsGotoed;
};

typedef struct Lexer Lexer;

char peek(Lexer* lex);
void next_char(Lexer* lex);
void lexer_aborted(Lexer*lex, char* ch);
void skip_white_space(Lexer* lex);
void skip_comment(Lexer* lex);
void delete_lexer(Lexer* lex);
Token get_token(Lexer* lex);
Lexer new_lexer(unsigned int size);
char* copy_from_source(int begin, Lexer* lex); 
Lexer init_lexer(char* path); 

#endif