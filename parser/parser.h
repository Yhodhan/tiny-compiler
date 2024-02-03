#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include "../token/token.h"

struct Parser {
  Lexer lexer;
  Token current_token; 
  Token peek_token;
};

typedef struct Parser Parser;

Parser init_parser(Lexer lex);
void parser_aborted(Parser *parser);
void match(Parser *parser, enum TokenType kind);
int check_peek(Parser *parser, enum TokenType kind);
int check_token(Parser *parser, enum TokenType kind);
void next_token(Parser *parser);

#endif