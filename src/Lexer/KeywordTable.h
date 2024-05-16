#include "Token.h"
#include <unordered_map>

class KeywordTable {
public:
    KeywordTable() {
        reserve(std::make_shared<Token>(TokenType::IF, "if"));
        reserve(std::make_shared<Token>(TokenType::THEN, "then"));
        reserve(std::make_shared<Token>(TokenType::BEGIN, "begin"));
        reserve(std::make_shared<Token>(TokenType::WHILE, "while"));
        reserve(std::make_shared<Token>(TokenType::DO, "do"));
        reserve(std::make_shared<Token>(TokenType::END, "end"));
    }

    std::shared_ptr<Token> getKeyword(const std::string& text) const;

private:
    void reserve(std::shared_ptr<Token> token);

    std::unordered_map<std::string, std::shared_ptr<Token>> keywords;
};
