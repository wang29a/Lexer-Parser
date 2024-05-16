#ifndef _header
#define _header
enum class TokenType {
  END_OF_FILE,// end of file
  UNKNOWN,  // for error

  // Group 1
  // lookhead = 1 (LA(1))
  DOT, POS, NEG,
  BEGIN,
  IF, THEN,
  WHILE, DO, END,
  ID,
  INT,
  WS,

  // Group 2
  // =, <>, <, <=, >, >=
  // +, -, *, /, ;, (, ), #
  // LA(2)
  EQ, NE, LT, LE, GT, GE,
  ADD, SUB, MUL, DIV, 
  SLA, SEM, LB, RB, HAS,

  // Group 3
  // arbitrary LA
  NUMBER,
  REAL,
  SCI,
};
#endif