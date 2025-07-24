#include "../include/MessagesHandler.hpp"
#include <regex>
#include <array>
#include <iostream>
MessagesHandler::MessagesHandler() {}

void MessagesHandler::ResolveMessage(const std::string& msg) {
    if(msg.find("POCKET_CARDS") != std::string::npos) {
        player->SetPocketCards(ResolvePocketCardsMessage(msg));
    }
    else if(msg.find("FLOP") != std::string::npos) {
        player->SetFlopCards(ResolveFlopMessage(msg));
    }
    else if(msg.find("ANOTHER_CARD") != std::string::npos) {
        player->AddExtraCard(ResolveAnotherCardMessage(msg));
    }
}

std::array<struct Card, pocket_cards> MessagesHandler::ResolvePocketCardsMessage(const std::string& msg) const {
    std::array<struct Card, pocket_cards> result;
    auto v = LiftCardsOutOfString(msg);
    for(unsigned int i  = 1 ; i < v.size() ;++i) result[i] = struct Card(v[i]);
    return result;
}

std::array<struct Card, flop_size> MessagesHandler::ResolveFlopMessage(const std::string& msg) const{
    std::array<struct Card, flop_size> result;
    auto v = LiftCardsOutOfString(msg);
    for(unsigned int i  = 1 ; i < v.size() ;++i) result[i] = struct Card(v[i]);
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

int MessagesHandler::ShellId(const std::string& msg) const {
    return std::stoi(LiftCardsOutOfString(msg)[0]);
}