#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include "../token/token.h"

struct Parser {
  Lexer lexer;
};

typedef struct Parser Parser;

#endif