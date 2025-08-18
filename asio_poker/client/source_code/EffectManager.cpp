#include "../include/EffectManager.hpp"
#include "../include/InfoPanel.hpp"
#include "../include/ActionPanel.hpp"
#include "../include/StatusBar.hpp"
#include "../include/GameStage.hpp"
#include "../include/Player.hpp"
#include "../include/StatusPanel.hpp"
#include "../include/EndGameDialog.hpp"
#include "../include/ClientFrame.hpp"
#include <wx/utils.h>
#include <wx/thread.h>
#include <wx/app.h>
wxDEFINE_EVENT(wxEVT_SOLO_WIN, wxCommandEvent);

DrawingCanvas* EffectManager::drawingCanvas = nullptr;
std::vector<InfoPanel*> EffectManager::players;
ActionPanel* EffectManager::actionPanel = nullptr;
StatusBar* EffectManager::statusBar = nullptr;
GameStage* EffectManager::gameStage = nullptr;
ClientFrame* EffectManager::clientFrame = nullptr;

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

void EffectManager::SwapToSmallBlind() {
    actionPanel->SetUpSmallBlind();
    //Kill(0);

}

void EffectManager::SwapToBigBlind() {
    actionPanel->SetUpBigBlind();
}

void EffectManager::SetStake(int id, int stake) {
    auto player = GetPlayerById(id);
    player->SetStake(stake);
    player->Refresh();
}

void EffectManager::SetPot(const std::string& newPot) {
    statusBar->SetPot(newPot);
    statusBar->Refresh();
}

void EffectManager::SetCards(int _id, struct Card& c1, struct Card& c2) {
    if(_id == Player::GetInstance().GetId()) return;
    auto player = GetPlayerById(_id);
    StatusPanel* playerCasted = dynamic_cast<StatusPanel*>(player);
    playerCasted->SetCards(c1,c2);
}

void EffectManager::SoloWin(int _id) {
    std::string msg;
    if(_id == Player::GetInstance().GetId()) msg = "You won";
    else {
        msg = "Player with id: " + std::to_string(_id) + " won.";
    }
    //wxCallAfter([msg, this] {
    //    EndGameDialog* dlg = new EndGameDialog(this->clientFrame, msg);
    //    dlg->ShowModal();
    //    dlg->Destroy(); 
    //});
    wxCommandEvent evt(wxEVT_SOLO_WIN);
    evt.SetString(msg);  // przekazujemy wiadomość
    clientFrame->GetEventHandler()->AddPendingEvent(evt);

}

void EffectManager::MultiWin(std::vector<int> ids) {

}

void EffectManager::UpdatePocket(int amount) {
    statusBar->SetWallet(amount);
}