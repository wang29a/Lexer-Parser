#ifndef _Token
#define _Token
#include <memory>
#include <string>
#include "header.h"
class Token{
public:
  static const std::shared_ptr<Token> EOF_TOKEN;
  static const std::shared_ptr<Token> WS_TOKEN;
  static const std::shared_ptr<Token> IF_TOKEN;
  static const std::shared_ptr<Token> THEN_TOKEN;
  static const std::shared_ptr<Token> WHILE_TOKEN;
  static const std::shared_ptr<Token> DO_TOKEN;
  static const std::shared_ptr<Token> END_TOKEN;
  static const std::shared_ptr<Token> BEGIN_TOKEN;
  static const std::shared_ptr<Token> EQ_TOKEN;
  static const std::shared_ptr<Token> NE_TOKEN;
  static const std::shared_ptr<Token> LT_TOKEN;
  static const std::shared_ptr<Token> LE_TOKEN;
  static const std::shared_ptr<Token> GT_TOKEN;
  static const std::shared_ptr<Token> GE_TOKEN;
  static const std::shared_ptr<Token> DOT_TOKEN;
  static const std::shared_ptr<Token> POS_TOKEN;
  static const std::shared_ptr<Token> NEG_TOKEN;

  Token(TokenType type, const std::string& text);
  auto getText() const -> std::string;

private:
  TokenType type;
  std::string text;
};
#endif