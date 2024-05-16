#include "WangLexer.h"
#include "Token.h"
#include <memory>

auto WangLexer::nextToken() -> std::shared_ptr<Token>{
    if (pos == input.length()) {
        return std::make_shared<Token>(TokenType::END_OF_FILE, "EOF");
    }
    std::shared_ptr<Token> token = nullptr;
    if (std::isspace(peek)) {
        token = WS();
    } else if (std::isalpha(peek)) {
        token = ID();
    } else if (std::isdigit(peek)) {
        token = NUMBER();
    } else if (peek == '=') {
        token = std::make_shared<Token>(TokenType::EQ, "=");
        advance();
    } else if (peek == '>') {
        advance();
        if (peek == '=') {
            token = std::make_shared<Token>(TokenType::GE, ">=");
            advance();
        } else {
            token = std::make_shared<Token>(TokenType::GT, ">");
        }
    } else if (peek == '<') {
        advance();
        if (peek == '=') {
            token = std::make_shared<Token>(TokenType::LE, "<=");
            advance();
        } else if (peek == '>') {
            token = std::make_shared<Token>(TokenType::NE, "<>");
            advance();
        } else {
            token = std::make_shared<Token>(TokenType::LT, "<");
        }
    } else if (peek == '.') {
        token = std::make_shared<Token>(TokenType::DOT, ".");
        advance();
    } else if (peek == '+') {
        token = std::make_shared<Token>(TokenType::POS, "+");
        advance();
    } else if (peek == '-') {
        token = std::make_shared<Token>(TokenType::NEG, "-");
        advance();
    } else if (peek == '*'){
        token = std::make_shared<Token>(TokenType::MUL, "*");
        advance();
    } else if (peek == '/'){
        token = std::make_shared<Token>(TokenType::DIV, "/");
        advance();
    } else if (peek == ';'){
        token = std::make_shared<Token>(TokenType::SEM, ";");
        advance();
    } else if (peek == '('){
        token = std::make_shared<Token>(TokenType::LB, "(");
        advance();
    } else if (peek == ')'){
        token = std::make_shared<Token>(TokenType::RB, ")");
        advance();
    } else if (peek == '#'){
        token = std::make_shared<Token>(TokenType::HAS, "#");
        advance();
    } else {
        token = std::make_shared<Token>(TokenType::UNKNOWN, std::string(1, peek));
        advance();
    }

    lastMatchPos = pos;
    return token;
};