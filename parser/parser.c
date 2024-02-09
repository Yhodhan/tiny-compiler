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
    parser_aborted();
  }
}

void next_token(Parser *parser){
  parser->current_token = parser->peek_token;
  parser->peek_token = get_token(&parser->lexer);
}

void parser_aborted(){
  printf("Error processing tokens \n");
  tfree();
  exit(EXIT_FAILURE);
}

void program(Parser *parser){
  printf("************************* \n");
  printf("         PROGRAM          \n");
  printf("************************* \n");

  // parse all the statements in the program
  while (!check_token(parser, EOF)) {
    statement(parser);
  }
}

void statement(Parser *parser){
  // check what kind of statement is 
  // PRINT (expression | string)
  if (check_token(parser, PRINT)){
    printf("************************* \n");
    printf("      STATEMENT PRINT     \n");
    printf("************************* \n");

    next_token(parser);

    if (check_token(parser, STRING)){
      next_token(parser);
    }
    // else {
      // expression(parser);
    // }
  }

  // newline
  nl(parser);
}

// void expression(Parser *parser) {
  
// }

void nl(Parser *parser){
  printf("*************************\n");
  printf("         NEWLINE         \n");
  printf("*************************\n");

  // require at least one newline
  match(parser, NEWLINE);
  while (check_token(parser, NEWLINE)){
    next_token(parser);
  }
}