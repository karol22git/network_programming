#include "../include/MessagesHandler.hpp"
#include <regex>
#include <array>
#include <iostream>
MessagesHandler::MessagesHandler() {}

std::array<struct Card, pocket_cards> MessagesHandler::ResolvePocketCardsMessage(const std::string& msg) const {
    std::array<struct Card, pocket_cards> result;
    auto v = LiftCardsOutOfString(msg);
    for(unsigned i  = i ; i < v.size() ;++i) result[i] = struct Card(v[i]);
    return result;
}

std::array<struct Card, flop_size> MessagesHandler::ResolveFlopMessage(const std::string& msg) const{
    std::array<struct Card, flop_size> result;
    auto v = LiftCardsOutOfString(msg);
    for(unsigned i  = i ; i < v.size() ;++i) result[i] = struct Card(v[i]);
    return result;
}

struct Card MessagesHandler::ResolveAnotherCardMessage(const std::string& msg) const {
    return LiftCardsOutOfString(msg)[0];
}

std::vector<std::string> MessagesHandler::LiftCardsOutOfString(const std::string& msg) const {
    std::vector<std::string> result;
    std::regex pattern("\\{([^}]*)\\}");
    std::smatch match;
    std::string::const_iterator start = msg.begin();
    std::string::const_iterator end = msg.end();
    unsigned int index = 0;
    while (std::regex_search(start, end, match, pattern)) {
        std::cout << "Znaleziono: " << match[1] << std::endl;
        result.push_back(match[1]);
        start = match[0].second;
    }
    return result;
}