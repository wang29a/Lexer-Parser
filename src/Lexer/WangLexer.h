#include "Lexer.h"
#include "KeywordTable.h"
#include "Token.h"
#include "header.h"
#include <cctype>
#include <memory>
#include <type_traits>

class WangLexer : Lexer{
public:
  WangLexer(std::string input) :Lexer(input){};
  auto nextToken() ->std::shared_ptr<Token>;

private:
  auto backToLongestMatch() -> std::shared_ptr<Token>;
  auto WS() -> std::shared_ptr<Token>{
    while (std::isspace(peek)) {
      advance();
    }
    return std::make_shared<Token>(TokenType::WS, "");
  }
  auto ID() -> std::shared_ptr<Token>{
    std::string sb;

    do {
      sb += peek;
      advance();
    } while (std::isalnum(peek));

    std::shared_ptr<Token> token = kwTable->getKeyword(sb);
    if (!token) {
        return std::make_shared<Token>(TokenType::ID, sb);
    }
    return token;
  }
  auto NUMBER() -> std::shared_ptr<Token>{
    std::string number;
    while (std::isdigit(peek)) {
      number += peek;
      advance();
    }
    return std::make_shared<Token>(TokenType::NUMBER, number);
  }
  int lastMatchPos = 0;
  int longestValidPrefixPos = 0;
  std::shared_ptr<TokenType> longestValidPrefixType = nullptr;

  std::shared_ptr<KeywordTable> kwTable;
};