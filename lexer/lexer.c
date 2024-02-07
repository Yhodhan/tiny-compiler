#include "lexer.h"

unsigned int file_size(FILE* fptr) {
   char ch;
   unsigned int size = 0;
   do {
     ch = fgetc(fptr);
     size++;
   } while(ch != EOF);

   return size;
}

void read_file(FILE* fptr, Lexer* lex){
  char ch;
  int i = 0;
  do {
    ch = fgetc(fptr);
    lex->source[i] = ch;
    i++;
  } while(ch != EOF);

  lex->source[i-1] = '\0';
}

Lexer init_lexer(char* path) {
  // get file size
  // return pointer to file init
  FILE* fptr = fopen(path, "r+");
  unsigned int size = file_size(fptr);
  rewind(fptr);

  // create lexer and copy source code
  Lexer lex = new_lexer(size);
  lex.source  = tmalloc(sizeof(char)*(size+1));  
  read_file(fptr, &lex);

  // close file descriptor
  fclose(fptr);
  return lex;
}

Lexer new_lexer(unsigned int size){
  Lexer lex = {
  .cur_pos = -1,
  .cur_char = ' ',
  .source_size = size,
  .source = NULL
  };

  return lex;
}

void delete_lexer(){
  tfree();
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
void lexer_aborted(char* ch){
  delete_lexer();
  printf("unknown token %s \n", ch);
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
  if (lex->cur_char == '#'){
    while (lex->cur_char != '\n') {
      next_char(lex);
    }
  }  
}

// copy string from specific location of source file
char* copy_from_source(int begin, Lexer* lex) {
  int end = lex->cur_pos;
  int size = end - begin + 1;
  char* buffer = tmalloc(sizeof(char) * (size+1));
  buffer[size] = '\0';

  int j = 0;
  for(int i = begin; i <= end; i++){
    buffer[j] = lex->source[i]; 
    j++;
  }

  return buffer;
}

// return the next token
Token get_token(Lexer* lex) {
  skip_white_space(lex);
  skip_comment(lex);
  char ch[2];
  ch[0] = lex->cur_char;  
  ch[1] = '\0';
  Token token;

  switch(ch[0]) {
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
      token = new_token(ch, END);   
    break;

    case '=':
      if (peek(lex) == '='){
        next_char(lex);
        token = new_token("==", EQEQ);
      }
      else {
        next_char(lex);
        token = new_token("=", EQ);
      }
    break;

    case '>':
      if (peek(lex) == '='){
        next_char(lex);
        token = new_token(">=", GTEQ);
      }
      else {
        token = new_token(">", GT);
      }
    break;

    case '<':
      if (peek(lex) == '='){
        next_char(lex);
        token = new_token("<=", LTEQ);
      }
      else {
        token = new_token("<", LT);
      }
    break;

    case '!':
      if (peek(lex) == '='){
        next_char(lex);
        token = new_token("!=", NOTEQ);
      }
      else {
        lexer_aborted("unknown character");
      }
    break;

    case '\"':
      // characters between quoatations
      next_char(lex);
      int begin = lex->cur_pos;

      while (lex->cur_char != '\"') {
        if (lex->cur_char == '\r' || lex->cur_char == '\n' || lex->cur_char == '\t' || lex->cur_char == '\\' || lex->cur_char == '\%'){
          lexer_aborted("Illegal character");
        }
        next_char(lex);
      }

      // extract string text from source 
      char* buffer = copy_from_source(begin, lex);

      token = new_token(buffer, STRING);      
    break;
      
    default:
      if (isdigit(ch[0])){
         int begin = lex->cur_pos;

         while (isdigit(peek(lex))){
           next_char(lex);
         }

         if(peek(lex) == '.') { // decimal
           next_char(lex);

           if (!isdigit(peek(lex))){
             lexer_aborted("Illegal character in number");
           }
           
           while (isdigit(peek(lex))){
             next_char(lex);
           }
         }

        char* buffer = copy_from_source(begin, lex);  
        token = new_token(buffer, NUMBER);      
      }
      else if (isalpha(ch[0])) {
        int begin = lex->cur_pos;

        while(isalnum(peek(lex))) {
          next_char(lex);
        }

        char* buffer = copy_from_source(begin, lex);
        int key = check_if_keyword(buffer);
        
        if (!key) {
          token = new_token(buffer, IDENT);      
        }
        else {
          token = new_token(buffer, key);      
        }
      }
      else
       lexer_aborted(ch);
  };

  next_char(lex);
  return token;
}


