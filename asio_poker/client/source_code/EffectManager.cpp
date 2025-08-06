#include "../include/EffectManager.hpp"
#include "../include/InfoPanel.hpp"
DrawingCanvas* EffectManager::drawingCanvas = nullptr;
std::vector<InfoPanel*> EffectManager::players;


EffectManager::EffectManager() {
}


void EffectManager::UpdateCurrentStake(const std::string& newStake) {
    //playerStatusBar->SetStake(newStake);
}

void EffectManager::HighlightCurrentPlayer(unsigned int _id) {
    auto lastPlayer = GetPlayerById(gmData.lastPlayerId);
    lastPlayer->SetBackgroundColour(*wxLIGHT_GREY);

    auto currentPlayer = GetPlayerById(_id);
    currentPlayer->SetBackgroundColour(*wxGREEN);

    gmData.lastPlayerId = _id;

    lastPlayer->Refresh();
    currentPlayer->Refresh();
}

InfoPanel* EffectManager::GetPlayerById(unsigned int _id) const {
    for(auto p: players) {
        if(p->GetId() == _id){//gmData.lastPlayerId) {
            return p;
        }
    }
    return nullptr;
}

void EffectManager::Kill(const unsigned int _id) {
    auto player = GetPlayerById(_id);
    player->SetBackgroundColour(*wxRED);
    player->Refresh();
}