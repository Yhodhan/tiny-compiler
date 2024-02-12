#include "parser.h"
#include <stdio.h>

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
  next_token(parser);
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

// --------------------------
//      grammar functions 
// --------------------------

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

  else if (check_token(parser, IF)){
    printf("    STATEMENT-IF \n");
    next_token(parser);
    comparison();
    match(parser, THEN);
    nl(parser);
    // Zero or more statements in the body
    while (!check_token(parser, ENDIF)){
      statement(parser);
    }
    match(parser, ENDIF);
  }

  else if (check_token(parser, WHILE)){
    printf("    STATEMENT-WHILE \n");
    next_token(parser);
    comparison();
    match(parser, REPEAT);
    nl(parser);
    // Zero or more statements in the body
    while (!check_token(parser, ENDWHILE)){
      statement(parser);
    }
    match(parser, ENDWHILE);
  }

  else if (check_token(parser, LABEL)){
    printf("    STATEMENT-LABEL \n");
    next_token(parser);
    match(parser, IDENT);
  }

  else if (check_token(parser, GOTO)){
    printf("    STATEMENT-GOTO \n");
    next_token(parser);
    match(parser, IDENT);
  }

  else if (check_token(parser, LET)){
    printf("    STATEMENT-LET \n");
    next_token(parser);
    match(parser, IDENT);
    match(parser, EQ);
    // expression(parser);
  }

  else if (check_token(parser, INPUT)){
    printf("    STATEMENT-INPUT \n");
    next_token(parser);
    match(parser, IDENT);
  }

  else {
    printf("Invalid statement at %s (%d) \n", parser->current_token.text, parser->current_token.type);
    parser_aborted();
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

// --------------------------
//      helper functions
// --------------------------

void comparison(){
}
