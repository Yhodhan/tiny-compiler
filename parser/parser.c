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
    .symbols = init_set(),
    .labels_declared = init_set(),
    .labels_gotoed = init_set(),
  };

  next_token(&parser);
  next_token(&parser);

  return parser;
}

void delete_parser(Parser* parser){
  delete_set(&parser->symbols);
  delete_set(&parser->labels_gotoed);
  delete_set(&parser->labels_declared);
  ufree();
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
  next_token(parser);
}

void next_token(Parser *parser){
  parser->current_token = parser->peek_token;
  parser->peek_token = get_token(&parser->lexer);
}

void parser_aborted(Parser* parser){
  delete_parser(parser);
  printf("Error processing tokens \n");
  exit(EXIT_FAILURE);
}

// --------------------------
//      grammar functions 
// --------------------------

void program(Parser *parser){
  printf("    PROGRAM \n");

  // parse all the statements in the program
  while (!check_token(parser, EOF)) {
    statement(parser);
  }

  for(unsigned int i = 0; i < parser->labels_gotoed.size; i++){
    if (!exists(&parser->labels_declared, parser->labels_gotoed.arr[i])){
        printf("Attend to GOTO to undeclared label: %s \n", parser->labels_gotoed.arr[i]);
        parser_aborted(parser);
    }  
  }
}

void statement(Parser *parser){
  // PRINT (expression | string)
  if (check_token(parser, PRINT)){
    printf("    STATEMENT PRINT \n");

    next_token(parser);

    if (check_token(parser, STRING)){
      next_token(parser);
    }
    else {
      expression(parser);
    }
  }

  else if (check_token(parser, IF)){
    printf("    STATEMENT-IF \n");
    next_token(parser);
    comparison(parser);
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
    comparison(parser);
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

    // check if label already exists
    if (exists(&parser->labels_declared, parser->current_token.text)){
      printf("Label already exists: %s \n", parser->current_token.text);
      parser_aborted(parser);
    }
    add(&parser->labels_declared, parser->current_token.text);
    
    match(parser, IDENT);
  }

  else if (check_token(parser, GOTO)){
    printf("    STATEMENT-GOTO \n");
    next_token(parser);
    add(&parser->labels_gotoed, parser->current_token.text);
    match(parser, IDENT);
  }

  else if (check_token(parser, LET)){
    printf("    STATEMENT-LET \n");
    next_token(parser);

    if (!exists(&parser->symbols, parser->current_token.text)){
      add(&parser->symbols, parser->current_token.text);
    }
    
    match(parser, IDENT);
    match(parser, EQ);
    expression(parser);
  }

  else if (check_token(parser, INPUT)){
    printf("    STATEMENT-INPUT \n");
    next_token(parser);

    if (!exists(&parser->symbols, parser->current_token.text)){
      add(&parser->symbols, parser->current_token.text);
    }
  
    match(parser, IDENT);
  }

  else {
    printf("Invalid statement at %s: (%d) \n", parser->current_token.text, parser->current_token.type);
    parser_aborted(parser);
  }
  // newline
  nl(parser);
}

// expression ::= term {( "-" | "+" ) term}
void expression(Parser *parser) {
  printf("    EXPRESSION \n");

  term(parser);
  // can have 0 or more +/- and expressions
  while (check_token(parser, PLUS) || check_token(parser, MINUS)){
    next_token(parser);
    term(parser);
  }
}

// term ::= unary {( "/" | "*" ) unary}
void term(Parser* parser){
    printf("    TERM\n");
    unary(parser);
    while (check_token(parser, ASTERISK) || check_token(parser, SLASH)){
      next_token(parser);
      unary(parser);
    }
}

// unary ::= ["+" | "-"] primary
void unary(Parser* parser){
  printf("    UNARY\n");
  if (check_token(parser, PLUS) || check_token(parser, MINUS)){
    next_token(parser);
  }
  primary(parser);
}

// primary ::= number | ident
void primary(Parser* parser){
  printf("    PRIMARY ( %s )\n", parser->current_token.text); 
  // can have 0 or more +/- and expressions
  if (check_token(parser, NUMBER)){
    next_token(parser);
  }
  else if (check_token(parser, IDENT)){
    // ensure the variable already exists
    if (!exists(&parser->symbols, parser->current_token.text)){
      printf("Referencing variable before assigment: %s \n", parser->current_token.text);
      parser_aborted(parser);
    }
    next_token(parser);
  }
  else {
    printf("Unexpected token at %s", parser->current_token.text);
    parser_aborted(parser);
  }
}

void nl(Parser *parser){
  printf("    NEWLINE \n");
  // require at least one newline
  match(parser, NEWLINE);
  while (check_token(parser, NEWLINE)){
    next_token(parser);
  }
}

void comparison(Parser *parser){
  printf("    COMPARISON \n");
  expression(parser);
  // must be at least one comparison operator and another expression 
  if (is_comparison_operator(parser)) {
    next_token(parser);
    expression(parser);
  }
  else {
    printf("Expected comparison operator at: %s (%d) \n", parser->current_token.text, parser->current_token.type);
    parser_aborted(parser);
  }

  // can have 0 or more comparison operator and expressions
  while (is_comparison_operator(parser)){
    next_token(parser);
    expression(parser);
  }
}

// --------------------------
//      helper functions
// --------------------------

int is_comparison_operator(Parser* parser){
  return check_token(parser, LT)   || 
         check_token(parser, GT)   ||
         check_token(parser, LTEQ) || 
         check_token(parser, GTEQ) ||
         check_token(parser, EQEQ) ||
         check_token(parser, NOTEQ);
}

