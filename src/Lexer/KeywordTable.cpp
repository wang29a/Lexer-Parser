#include "KeywordTable.h"
std::shared_ptr<Token> KeywordTable::getKeyword(const std::string& text) const {
    auto it = keywords.find(text);
    if (it != keywords.end()) {
        return it->second;
    }
    return nullptr;
}

void KeywordTable::reserve(std::shared_ptr<Token> token) {
    keywords[token->getText()] = token;
}
