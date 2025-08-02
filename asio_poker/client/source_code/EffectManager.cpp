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
    lastPlayer->SetBackgroundColour(*wxWHITE);

    auto currentPlayer = GetPlayerById(_id);
    currentPlayer->SetBackgroundColour(*wxGREEN);

    gmData.lastPlayerId = _id;

    lastPlayer->Refresh();
    currentPlayer->Refresh();
}

InfoPanel* EffectManager::GetPlayerById(unsigned int _id) const {
    for(auto p: players) {
        if(p->GetId() == gmData.lastPlayerId) {
            return p;
        }
    }
    return nullptr;
}