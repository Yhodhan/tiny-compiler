#include "parser.h"

Parser init_parser(Lexer lex){
  Token token = {
    .text = NULL,
    .type = NEW,
  };

  Parser parser = {
    .lexer = lex,
    .current_token = token,
    .peek_token = token,
  };

  next_token(&parser);
  next_token(&parser);

  return parser;
}

int check_peek(Parser *parser, enum TokenType kind){
  return kind == parser->peek_token.type;
}

int check_token(Parser *parser, enum TokenType kind){
  return kind == parser->current_token.type;
}

void match(Parser *parser, enum TokenType kind){
  if (!check_token(parser, kind)){
    parser_aborted(parser);
  }
}

void next_token(Parser *parser){
  parser->current_token = parser->peek_token;
  parser->peek_token = get_token(&parser->lexer);
}

void parser_aborted(Parser *parser){
  delete_lex(&parser->lexer);
  printf("Error processing tokens");
  exit(1);
}