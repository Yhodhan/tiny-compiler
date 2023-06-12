#include "token.h"

Token new_token(char ch, enum TokenType type){
  Token token;
  token.text = ch;
  token.type = type;
  return token;
}