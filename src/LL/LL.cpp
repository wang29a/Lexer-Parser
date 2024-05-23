#include "LL.h"
#include <memory>
#include <stack>
#include <iostream>

// Function to compute FIRST set
std::unordered_map<Symbol, std::unordered_set<Symbol>> computeFirst(const Grammar& grammar) {
    std::unordered_map<Symbol, std::unordered_set<Symbol>> first;

    // Initialize FIRST sets for all non-terminals
    for (const auto& [non_terminal, _] : grammar) {
        first[non_terminal] = {};
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& [non_terminal, rules] : grammar) {
            for (const auto& rule : rules) {
                for (const auto& symbol : rule) {
                    if (!grammar.count(symbol)) {  // terminal
                        if (first[non_terminal].insert(symbol).second) {
                            changed = true;
                        }
                        break;
                    } else {  // non-terminal
                        auto& firstSet = first[symbol];
                        size_t beforeSize = first[non_terminal].size();
                        first[non_terminal].insert(firstSet.begin(), firstSet.end());
                        if (first[non_terminal].size() > beforeSize) {
                            changed = true;
                        }
                        if (firstSet.find("ε") == firstSet.end()) {
                            break;
                        }
                    }
                }
            }
        }
    }

    return first;
}

// Function to compute FOLLOW set
std::unordered_map<Symbol, std::unordered_set<Symbol>> computeFollow(const Grammar& grammar, const std::unordered_map<Symbol, std::unordered_set<Symbol>>& first, const Symbol& startSymbol) {
    std::unordered_map<Symbol, std::unordered_set<Symbol>> follow;

    // Initialize FOLLOW sets for all non-terminals
    for (const auto& [non_terminal, _] : grammar) {
        follow[non_terminal] = {};
    }

    // FOLLOW(startSymbol) contains end-of-input marker $
    follow[startSymbol].insert("$");

    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& [non_terminal, rules] : grammar) {
            for (const auto& rule : rules) {
                for (size_t i = 0; i < rule.size(); ++i) {
                    const auto& symbol = rule[i];
                    if (grammar.count(symbol)) {  // non-terminal
                        size_t beforeSize = follow[symbol].size();

                        if (i + 1 < rule.size()) {
                            const auto& nextSymbol = rule[i + 1];
                            if (!grammar.count(nextSymbol)) {  // terminal
                                follow[symbol].insert(nextSymbol);
                            } else {  // non-terminal
                                auto& firstSet = first.at(nextSymbol);
                                follow[symbol].insert(firstSet.begin(), firstSet.end());
                                follow[symbol].erase("ε");
                                if (firstSet.find("ε") != firstSet.end()) {
                                    follow[symbol].insert(follow[non_terminal].begin(), follow[non_terminal].end());
                                }
                            }
                        } else {
                            follow[symbol].insert(follow[non_terminal].begin(), follow[non_terminal].end());
                        }

                        if (follow[symbol].size() > beforeSize) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }

    return follow;
}

// Function to compute SELECT set
std::unordered_map<RulePair, std::unordered_set<Symbol>> computeSelect(const Grammar& grammar, const std::unordered_map<Symbol, std::unordered_set<Symbol>>& first, const std::unordered_map<Symbol, std::unordered_set<Symbol>>& follow) {
    std::unordered_map<RulePair, std::unordered_set<Symbol>> select;

    std::string Epsilon("ε");
    for (const auto& [non_terminal, rules] : grammar) {
        for (const auto& rule : rules) {
            std::unordered_set<Symbol> selectSet;
            bool hasEpsilon = true;
            for (const auto& symbol : rule) {
                // if (!grammar.count(symbol) && symbol != Epsilon) {  // terminal
                if (!grammar.count(symbol)) {  // terminal
                    if (symbol != Epsilon) {
                        selectSet.insert(symbol);
                        hasEpsilon = false;
                    }
                    break;
                } else {  // non-terminal
                    auto& firstSet = first.at(symbol);
                    selectSet.insert(firstSet.begin(), firstSet.end());
                    if (firstSet.find("ε") == firstSet.end()) {
                        hasEpsilon = false;
                        break;
                    }
                }
            }
            if (hasEpsilon) {
                auto& followSet = follow.at(non_terminal);
                selectSet.insert(followSet.begin(), followSet.end());
            }
            select[{non_terminal, rule}] = selectSet;
        }
    }

    return select;
}
// Function to build the LL(1) parsing table
std::unordered_map<Symbol, std::unordered_map<Symbol, Rule>> buildParsingTable(
    const Grammar& grammar, const std::unordered_map<Symbol, std::unordered_set<Symbol>>& first, 
    const std::unordered_map<Symbol, std::unordered_set<Symbol>>& follow, 
    const std::unordered_map<RulePair, std::unordered_set<Symbol>>& select
    ) {
    std::unordered_map<Symbol, std::unordered_map<Symbol, Rule>> parsingTable;

    for (const auto& [rulePair, selectSet] : select) {
        for (const auto& terminal : selectSet) {
            parsingTable[rulePair.non_terminal][terminal] = rulePair.rule;
        }
    }

    return parsingTable;
}

// Function to perform LL(1) parsing
bool parseString(const Grammar& grammar, const Symbol& startSymbol, const std::unordered_map<Symbol, std::unordered_map<Symbol, Rule>>& parsingTable, const std::vector<std::shared_ptr<Token>>& input) {
    std::stack<Symbol> parsingStack;
    parsingStack.push("$");
    parsingStack.push(startSymbol);

    size_t index = 0;
    while (!parsingStack.empty()) {
        Symbol top = parsingStack.top();
        parsingStack.pop();

        if (top == "$") {
            return index == input.size();
        } else if (!grammar.count(top)) {  // terminal
            if (top == input[index]->getType()) {
                std::cout<<"成功匹配："<<top<<" "<<input[index]->getText()<<std::endl;
                index++;
            } else {
                return false;
            }
        } else {  // non-terminal
            if (parsingTable.at(top).count(input[index]->getType())) {
                const Rule& rule = parsingTable.at(top).at(input[index]->getType());
                for (auto it = rule.rbegin(); it != rule.rend(); ++it) {
                    if (*it != "ε") {
                        parsingStack.push(*it);
                    }
                }
            } else {
                return false;
            }
        }
    }

    return index == input.size();
}

int process(std::vector<std::shared_ptr<Token>> &input) {
// int main() {
    Grammar grammar = {
        {"program",{{"begin","stmts","end",},}},
        {"stmts",{{"stmt","stmtsas",},}},
        {"stmtsas",{{";","stmt","stmtsas",},{"ε",},}},
        {"stmt",{{"ID",":=","exp",},}},
        {"exp",{{"item","items",},}},
        {"items",{{"+","item","items",},{"-", "item","items",},{"ε",},}},
        {"item",{{"factor","factors",},}},
        {"factors",{{"*","factor","factors",},{"/","factor","factors"}, {"ε"}}},
        {"factor",{{"ε",},{"ID",},{"NUM",},{"(","exp",")",},}},
    };
    Symbol startSymbol = "program";
    // Grammar grammar = {
    //     {"E", {{"T", "E'"}}},
    //     {"E'", {{"+", "T", "E'"}, {"ε"}}},
    //     {"T", {{"F", "T'"}}},
    //     {"T'", {{"*", "F", "T'"}, {"ε"}}},
    //     {"F", {{"(", "E", ")"}, {"id"}}}
    // };

    // Symbol startSymbol = "E";
    // Grammar grammar = {
    //     {"A", {{"a", "B"}, {"d"}}},
    //     {"B", {{"b", "B", "A"}, {"ε"}}},
    // };

    // Symbol startSymbol = "A";
    // Grammar grammar = {
    //     {"S", {{"A", "B"}, {"b", "c"}}},
    //     {"A", {{"b"}, {"ε"}}},
    //     {"B", {{"a", "D'"}, {"ε"}}},
    //     {"C", {{"A", "D"}, {"ε"}}},
    //     {"D", {{"a", "S"}, {"c"}}}
    // };

    // Symbol startSymbol = "S";

    auto first = computeFirst(grammar);
    auto follow = computeFollow(grammar, first, startSymbol);
    auto select = computeSelect(grammar, first, follow);
    auto parsingTable = buildParsingTable(grammar, first, follow, select);                   

    // Output FIRST sets
    std::cout << "FIRST sets:" << std::endl;
    for (const auto& [non_terminal, firstSet] : first) {
        std::cout << "FIRST(" << non_terminal << ") = { ";
        for (const auto& symbol : firstSet) {
            std::cout << symbol << " ";
        }
        std::cout << "}" << std::endl;
    }

    // Output FOLLOW sets
    std::cout << "FOLLOW sets:" << std::endl;
    for (const auto& [non_terminal, followSet] : follow) {
        std::cout << "FOLLOW(" << non_terminal << ") = { ";
        for (const auto& symbol : followSet) {
            std::cout << symbol << " ";
        }
        std::cout << "}" << std::endl;
    }

    // Output SELECT sets
    std::cout << "SELECT sets:" << std::endl;
    for (const auto& [rulePair, selectSet] : select) {
        std::cout << "SELECT(" << rulePair.non_terminal << " -> ";
        for (const auto& symbol : rulePair.rule) {
            std::cout << symbol << " ";
        }
        std::cout << ") = { ";
        for (const auto& symbol : selectSet) {
            std::cout << symbol << " ";
        }
        std::cout << "}" << std::endl;
    }
    //std::vector<Symbol> input = {"a", "b", "d", "$"};
    bool result = parseString(grammar, startSymbol, parsingTable, input);

    std::cout << "Input std::string is " << (result ? "accepted" : "rejected") << " by the grammar." << std::endl;
    return 0;
}
