#include "Token.h"
#include "header.h"

Token::Token(TokenType type, const std::string& text) : type(type), text(text) {}

std::string Token::getText() const {
    return text;
}
std::string Token::getType() const {
    if (type != TokenType::ID || type != TokenType::NUMBER) {
        return text;
    }else if (type == TokenType::ID) {
        return "ID";
    }else {
        return "NUMBER";
    }
}

const std::shared_ptr<Token> Token::EOF_TOKEN = std::make_shared<Token>(TokenType::END_OF_FILE, "EOF");
const std::shared_ptr<Token> Token::WS_TOKEN = std::make_shared<Token>(TokenType::WS, " ");
const std::shared_ptr<Token> Token::IF_TOKEN = std::make_shared<Token>(TokenType::IF, "if");
const std::shared_ptr<Token> Token::THEN_TOKEN = std::make_shared<Token>(TokenType::THEN, "then");
const std::shared_ptr<Token> Token::WHILE_TOKEN = std::make_shared<Token>(TokenType::WHILE, "while");
const std::shared_ptr<Token> Token::DO_TOKEN = std::make_shared<Token>(TokenType::DO, "do");
const std::shared_ptr<Token> Token::BEGIN_TOKEN = std::make_shared<Token>(TokenType::END, "begin");
const std::shared_ptr<Token> Token::EQ_TOKEN = std::make_shared<Token>(TokenType::EQ, "=");
const std::shared_ptr<Token> Token::NE_TOKEN = std::make_shared<Token>(TokenType::NE, "<>");
const std::shared_ptr<Token> Token::LT_TOKEN = std::make_shared<Token>(TokenType::LT, "<");
const std::shared_ptr<Token> Token::LE_TOKEN = std::make_shared<Token>(TokenType::LE, "<=");
const std::shared_ptr<Token> Token::GT_TOKEN = std::make_shared<Token>(TokenType::GT, ">");
const std::shared_ptr<Token> Token::GE_TOKEN = std::make_shared<Token>(TokenType::GE, ">=");
const std::shared_ptr<Token> Token::DOT_TOKEN = std::make_shared<Token>(TokenType::DOT, ".");
const std::shared_ptr<Token> Token::POS_TOKEN = std::make_shared<Token>(TokenType::POS, "+");
const std::shared_ptr<Token> Token::NEG_TOKEN = std::make_shared<Token>(TokenType::NEG, "-");

const std::shared_ptr<Token> Token::MUL_TOKEN = std::make_shared<Token>(TokenType::MUL, "*");
const std::shared_ptr<Token> Token::DIV_TOKEN = std::make_shared<Token>(TokenType::DIV, "/");
const std::shared_ptr<Token> Token::SEM_TOKEN = std::make_shared<Token>(TokenType::SEM, ";");
const std::shared_ptr<Token> Token::LB_TOKEN = std::make_shared<Token>(TokenType::LB, "(");
const std::shared_ptr<Token> Token::RB_TOKEN = std::make_shared<Token>(TokenType::RB, ")");
const std::shared_ptr<Token> Token::HAS_TOKEN = std::make_shared<Token>(TokenType::HAS, "#");