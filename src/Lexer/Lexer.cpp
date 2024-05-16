#include "Lexer.h"
void Lexer::advance() {
  pos++;
  if (pos >= input.length()) {
      peek = '\0';
  } else {
      peek = input[pos];
  }
}

void Lexer::reset(int pos) {
  this->pos = pos;
  if (pos >= input.length()) {
      peek = '\0';
  } else {
      peek = input[pos];
  }
}