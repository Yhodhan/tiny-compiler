#include "parser.h"

Parser init_parser(Lexer lex){
  Parser parser = {
    .lexer = lex
  };

  return parser;
}

int check_peek(Parser *parser, enum TokenType kind){
  return 1;
}

int check_token(Parser *parser, enum TokenType kind){
  return 1;
}

void match(Parser *parser, enum TokenType kind){
  
}

void nextToken(Parser *parser){
  
}

void parser_aborted(Parser *parser, char* message){
  
}