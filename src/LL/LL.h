#ifndef _LL_H
#define _LL_H
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include "../Lexer/Token.h"


// Define some type aliases for readability
using Symbol = std::string;
using Rule = std::vector<Symbol>;
using Grammar = std::unordered_map<Symbol, std::vector<Rule>>;

// Custom struct to hold a pair of Symbol and Rule
struct RulePair {
    Symbol non_terminal;
    Rule rule;

    bool operator==(const RulePair& other) const {
        return non_terminal == other.non_terminal && rule == other.rule;
    }
};

// Custom hash function for RulePair
namespace std {
    template<>
    struct hash<RulePair> {
        size_t operator()(const RulePair& rp) const {
            size_t hash1 = hash<Symbol>{}(rp.non_terminal);
            size_t hash2 = 0;
            for (const auto& sym : rp.rule) {
                hash2 ^= hash<Symbol>{}(sym) + 0x9e3779b9 + (hash2 << 6) + (hash2 >> 2);
            }
            return hash1 ^ hash2;
        }
    };
}


std::unordered_map<Symbol, std::unordered_set<Symbol>> computeFirst(const Grammar& grammar);

std::unordered_map<Symbol, std::unordered_set<Symbol>> computeFollow(const Grammar& grammar, const std::unordered_map<Symbol, std::unordered_set<Symbol>>& first, const Symbol& startSymbol);

std::unordered_map<RulePair, std::unordered_set<Symbol>> computeSelect(const Grammar& grammar, const std::unordered_map<Symbol, std::unordered_set<Symbol>>& first, const std::unordered_map<Symbol, std::unordered_set<Symbol>>& follow);

std::unordered_map<Symbol, std::unordered_map<Symbol, Rule>> buildParsingTable(const Grammar& grammar, const std::unordered_map<Symbol, std::unordered_set<Symbol>>& first, const std::unordered_map<Symbol, std::unordered_set<Symbol>>& follow, const std::unordered_map<RulePair, std::unordered_set<Symbol>>& select);

bool parseString(const Grammar& grammar, const Symbol& startSymbol, const std::unordered_map<Symbol, std::unordered_map<Symbol, Rule>>& parsingTable, const std::vector<std::shared_ptr<Token>>& input);

int process(std::vector<std::shared_ptr<Token>> &input);
#endif