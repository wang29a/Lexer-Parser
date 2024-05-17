#ifndef _Token
#define _Token
#include <iostream>
#include <ostream>
#include <fmt/format.h>
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
  static const std::shared_ptr<Token> MUL_TOKEN;
  static const std::shared_ptr<Token> DIV_TOKEN;
  static const std::shared_ptr<Token> SEM_TOKEN;
  static const std::shared_ptr<Token> LB_TOKEN;
  static const std::shared_ptr<Token> RB_TOKEN;
  static const std::shared_ptr<Token> HAS_TOKEN;
  static const std::shared_ptr<Token> DOT_TOKEN;
  static const std::shared_ptr<Token> POS_TOKEN;
  static const std::shared_ptr<Token> NEG_TOKEN;

  Token(TokenType type, const std::string& text);
  auto getText() const -> std::string;

  friend std::ostream& operator<<(std::ostream& os, const Token& obj){
    std::string type;
    if (obj.type != TokenType::ID) {
      type = obj.text;
    }else {
      type = "ID";
    }
    std::string out = fmt::format("token type : {}, text : {}", type, obj.text);
    std::cout<<out<<"\n";
    // os << out;
    return os;
  }

private:
  TokenType type;
  std::string text;
};
#endif