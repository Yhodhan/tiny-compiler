#include "lexer.h"

Lexer new_lex(unsigned int size){
  Lexer lex;
  lex.cur_pos = -1;
  lex.cur_char = ' ';
  lex.source_size = size;
  lex.source = NULL;
  return lex;
}

void delete_lex(Lexer* lex){
  free(lex->source);
  lex->source = NULL;
}
 // process next character
void next_char(Lexer* lex) {
  lex->cur_pos++;
  if (lex->cur_pos >= lex->source_size){
    lex->cur_char = '\0'; // EOF
  }  
  lex->cur_char = lex->source[lex->cur_pos];
}

// return the loookhead character
char peek(Lexer* lex){
  if (lex->cur_pos+1 >= lex->source_size){
    return '\0';
  }
  return lex->source[lex->cur_pos+1];
}

// invalid token found, print error message and exit
void aborted(Lexer* lex, char ch){
  delete_lex(lex);
  printf("unknown token %c \n", ch);
  exit(1);
}
// skip whitespace execpt newlines
void skip_white_space(Lexer* lex){
  char ch = lex->cur_char;
  while(ch == ' ' || ch == '\t' || ch == '\r') {
    next_char(lex);
    ch = lex->cur_char;
  }
}
// skip comments in the code
void skip_comment(Lexer* lex){
  
}
// return the next token
Token get_token(Lexer* lex) {
  skip_white_space(lex);
  char ch = lex->cur_char;  
  Token token;

  switch(ch) {
    case '+':
      token = new_token(ch, PLUS);   
    break;
    case '-':
      token = new_token(ch, MINUS);   
    break;
    case '*':
      token = new_token(ch, ASTERISK);   
    break;
    case '/':
      token = new_token(ch, SLASH);   
    break;
    case '\n':
      token = new_token(ch, NEWLINE);   
    break;
    case '\0':
      token = new_token(ch, EOF);   
    break;
    case '=':
      if (peek(lex) == '='){
        next_char(lex);
        token = new_token('=', EQEQ);
      }
      else {
        next_char(lex);
        token = new_token('=', EQ);
      }
    break;
    case '>':
      if (peek(lex) == '='){
        next_char(lex);
        token = new_token( '>', GTEQ);
      }
      else {
        token = new_token('>', GT);
      }
    break;
    case '<':
      if (peek(lex) == '='){
        next_char(lex);
        token = new_token( '<', LTEQ);
      }
      else {
        token = new_token('<', LT);
      }
    break;
    case '!':
      if (peek(lex) == '='){
        next_char(lex);
        token = new_token('!', NOTEQ);
      }
      else {
        aborted(lex, ch);
      }
    break;
    default:
      aborted(lex, ch);
  };

  return token;
}



