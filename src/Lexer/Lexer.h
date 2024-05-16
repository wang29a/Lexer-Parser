#include <cstddef>
#include <memory>
#include <string>
#include "Token.h"
class Lexer {
public:
  Lexer(const std::string& input) : input(input), peek(input[0]), pos(0) {}
  virtual ~Lexer() = default;
  virtual std::shared_ptr<Token> nextToken() = 0;
  void advance();
  void reset(int pos);
protected:
  std::string input;
  char peek;
  std::size_t pos;
};