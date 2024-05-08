#ifndef LEXER_H
#define LEXER_H

#include "../set/set.h"
#include "../token/token.h"
#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>

struct Lexer {
  char *source;
  char cur_char;
  int cur_pos;
  int source_size;
};

typedef struct Lexer Lexer;

char peek(Lexer *lex);
void next_char(Lexer *lex);
Token get_token(Lexer *lex);
Lexer init_lexer(char *path);
void lexer_aborted(char *ch);
void skip_comment(Lexer *lex);
void skip_white_space(Lexer *lex);
Lexer new_lexer(unsigned int size);
char *copy_from_source(int begin, Lexer *lex);

#endif