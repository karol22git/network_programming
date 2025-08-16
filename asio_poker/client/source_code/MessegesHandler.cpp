#include "../include/MessagesHandler.hpp"
#include "../include/EffectManager.hpp"
#include "../include/DrawingCanvas.hpp"
#include "../include/GameStage.hpp"
#include <regex>
#include <array>
#include <iostream>
MessagesHandler::MessagesHandler(): effectManager(new EffectManager()) {}

void MessagesHandler::ResolveMessage(const std::string& msg) {
    if(msg.find("POCKET_CARDS") != std::string::npos) {
        player->SetPocketCards(ResolvePocketCardsMessage(msg));
        //EffectManager::drawingCanvas->FillPocketCards(ResolvePocketCardsMessage(msg));
        EffectManager::gameStage->FillPocketCards(ResolvePocketCardsMessage(msg));
       //for(auto c: ResolvePocketCardsMessage(msg)) debugConsole->LogMessage(resource_dir+c.toString());

    }
    else if(msg.find("FLOP") != std::string::npos) {
        std::cout<<"FLOP: "<<msg<<std::endl;
        player->SetFlopCards(ResolveFlopMessage(msg));
        //EffectManager::drawingCanvas->FillFlopCards(ResolveFlopMessage(msg));
        EffectManager::gameStage->FillFlopCards(ResolveFlopMessage(msg));
    }
    else if(msg.find("ANOTHER_CARD") != std::string::npos) {
        player->AddExtraCard(ResolveAnotherCardMessage(msg));
        //EffectManager::drawingCanvas->AddAnotherCard(ResolveAnotherCardMessage(msg));
        EffectManager::gameStage->AddAnotherCard(ResolveAnotherCardMessage(msg));
    }
    else if(msg.find("TURN") != std::string::npos) {
        effectManager->HighlightCurrentPlayer(ShellId(msg));
    }
    else if(msg.find("EXIT") != std::string::npos) {
        effectManager->Kill(ShellId(msg));
    }
    else if(msg.find("SMALL_BLIND") != std::string::npos) {
        effectManager->SwapToSmallBlind();
    }
    else if(msg.find("BIG_BIND") != std::string::npos) {
        
    }
    else if(msg.find("ACCEPT_CALL") != std::string::npos) {
        ResolveAcceptCallMessage(msg);
    }
    else if(msg.find("STAKE") != std::string::npos) {
        ResolveStakeMessage(msg);
    }
    else if(msg.find("POT") != std::string::npos) {
        ResolvePotMessage(msg);
    }
    else if(msg.find("SHOW_CARDS") != std::string::npos) {
        ResolveShowCardsMessage(msg);
    }
    else if(msg.find("SOLO_WIN") != std::string::npos) {
        ResolveSoloWinMessage(msg);
    }
    else if(msg.find("MULTI_WIN") != std::string::npos) {
        ResolveMultiWinMessage(msg);
    }
}

std::array<struct Card, pocket_cards> MessagesHandler::ResolvePocketCardsMessage(const std::string& msg) const {
    std::array<struct Card, pocket_cards> result;
    auto v = LiftCardsOutOfString(msg);
    for(unsigned int i  = 0 ; i < v.size() ;++i) result[i] = struct Card(v[i]);
    return result;
}

std::array<struct Card, flop_size> MessagesHandler::ResolveFlopMessage(const std::string& msg) const{
    std::array<struct Card, flop_size> result;
    auto v = LiftCardsOutOfString(msg);
    for(unsigned int i  = 0 ; i < v.size() ;++i) result[i] = struct Card(v[i]);
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
        //std::cout << "Znaleziono: " << match[1] << std::endl;
        result.push_back(match[1]);
        start = match[0].second;
    }
    return result;
}

int MessagesHandler::ShellId(const std::string& msg) const {
    return std::stoi(LiftCardsOutOfString(msg)[0]);
    //return 0;
}

void MessagesHandler::SetPlayer(Player* p) {
    player = p;
}

void MessagesHandler::SetDebugger(DebugConsole* db) {
    debugConsole = db;
}

void MessagesHandler::ResolveKillMessage(const std::string& msg) {
    auto _id = ShellId(msg);
}

void MessagesHandler::ResolveAcceptCallMessage(const std::string& msg) {
    player->SetMoneyLeft(ShellId(msg));
}

void MessagesHandler::ResolveStakeMessage(const std::string& msg) {
    auto args = GetAllParameters(msg);
    auto id = std::stoi(args[0]);
    auto stake = std::stoi(args[1]);
    effectManager->SetStake(id,stake);
}

std::vector<std::string> MessagesHandler::GetAllParameters(const std::string& msg) const {
    return LiftCardsOutOfString(msg);
}

std::string MessagesHandler::ShellFirstParameter(const std::string& msg) const {
    return LiftCardsOutOfString(msg)[0];
}

void MessagesHandler::ResolvePotMessage(const std::string& msg) {
    auto newPot = ShellFirstParameter(msg);
    effectManager->SetPot(newPot);
}   

void MessagesHandler::ResolveShowCardsMessage(const std::string& msg) {
    auto allParameters = GetAllParameters(msg);
    int id = std::stoi(allParameters[0]);
    struct Card c1(allParameters[1]);
    struct Card c2(allParameters[2]);
    effectManager->SetCards(id,c1,c2);
}

void MessagesHandler::ResolveSoloWinMessage(const std::string& msg) {
    int id = std::stoi(ShellFirstParameter(msg));
    effectManager->SoloWin(id);
}

void MessagesHandler::ResolveMultiWinMessage(const std::string& msg) {
    auto allParameters = GetAllParameters(msg);
    std::vector<int> ids;
    for(auto parameter: allParameters) ids.push_back(std::stoi(parameter));
    effectManager->MultiWin(ids);
}