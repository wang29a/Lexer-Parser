#include "WangLexer.h"
#include "Token.h"
#include "header.h"
#include <memory>

auto WangLexer::nextToken() -> std::shared_ptr<Token>{
    if (pos == input.length()) {
        return Token::EOF_TOKEN;
    }
    std::shared_ptr<Token> token = nullptr;
    if (std::isspace(peek)) {
        token = WS();
    } else if (std::isalpha(peek)) {
        token = ID();
    } else if (std::isdigit(peek)) {
        token = NUMBER();
    } else if (peek == '=') {
        token = Token::EQ_TOKEN;
        advance();
    } else if (peek == '>') {
        advance();
        if (peek == '=') {
            token = Token::GE_TOKEN;
            advance();
        } else {
            token = Token::GT_TOKEN;
        }
    } else if (peek == '<') {
        advance();
        if (peek == '=') {
            token = Token::LE_TOKEN;
            advance();
        } else if (peek == '>') {
            token = Token::NE_TOKEN;
            advance();
        } else {
            token = Token::LT_TOKEN;
        }
    } else if (peek == '.') {
        token = Token::DOT_TOKEN;
        advance();
    } else if (peek == '+') {
        token = Token::POS_TOKEN;
        advance();
    } else if (peek == '-') {
        token = Token::NEG_TOKEN;
        advance();
    } else if (peek == '*'){
        token = Token::MUL_TOKEN;
        advance();
    } else if (peek == '/'){
        token = Token::DIV_TOKEN;
        advance();
    } else if (peek == ';'){
        token = Token::SEM_TOKEN;
        advance();
    } else if (peek == '('){
        token = Token::LB_TOKEN;
        advance();
    } else if (peek == ')'){
        token = Token::RB_TOKEN;
        advance();
    } else if (peek == '#'){
        token = Token::HAS_TOKEN;
        advance();
    } else {
        token = std::make_shared<Token>(TokenType::UNKNOWN, std::string(1, peek));
        advance();
    }

    lastMatchPos = pos;
    return token;
};