#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include "../token/token.h"

struct Parser {
  Lexer lexer;
  Token current_token; 
  Token peek_token;
  Set symbols;
  Set labels_declared;
  Set labels_gotoed;
};

typedef struct Parser Parser;

void nl(Parser *parser);
void term(Parser* parser);
void unary(Parser* parser);
void program(Parser *parser);
void primary(Parser* parser);
Parser init_parser(Lexer lex);
void statement(Parser *parser);
void next_token(Parser *parser);
void expression(Parser *parser);
void comparison(Parser* parser);
void expression(Parser *parser); 
void delete_parser(Parser* parser);
void parser_aborted(Parser* parser);
int is_comparison_operator(Parser* parser);
void match(Parser *parser, enum TokenType kind);
int check_peek(Parser *parser, enum TokenType kind);
int check_token(Parser *parser, enum TokenType kind);

#endif