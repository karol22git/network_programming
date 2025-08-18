#include "../include/RightSidePanel.hpp"
#include "../include/Player.hpp"

RightSidePanel::RightSidePanel(wxWindow* parent, wxSize size): SidePanel(parent, size) {
    ArrangePanel();
}

void RightSidePanel::ArrangePanel() {
    playerStatusPanelA = new StatusPanel(handlerPanel,playerStatusAPanelPosition,wxSize(playerStatsPanelWidth,playerStatusPanelHeight),std::to_string((Player::GetInstance().GetId() + 1) % 5));
    playerACards = new PlayerCardsPanel(handlerPanel,playerASubpanelPoistion,wxSize(playerStatsPanelWidth,playerCardsPanelHeight));
    playerStatusPanelB = new StatusPanel(handlerPanel,playerStatusBPanelPosition,wxSize(playerStatsPanelWidth,playerStatusPanelHeight),std::to_string((Player::GetInstance().GetId() + 2) % 5));
    playerBCards = new PlayerCardsPanel(handlerPanel,playerBSubpanelPosition,wxSize(playerStatsPanelWidth,playerCardsPanelHeight));
    playerStatusPanelA->SetId((Player::GetInstance().GetId() + step) % margin);
    playerStatusPanelB->SetId((Player::GetInstance().GetId() + 2*step) % margin);
    auto playerStatusPanelACasted = dynamic_cast<StatusPanel*>(playerStatusPanelA);
    auto playerStatusPanelBCasted = dynamic_cast<StatusPanel*>(playerStatusPanelB);
    playerStatusPanelACasted->SetCardsPanel(playerACards);
    playerStatusPanelBCasted->SetCardsPanel(playerBCards);
    AddStatusPanelToEffectManager(playerStatusPanelA);
    AddStatusPanelToEffectManager(playerStatusPanelB);
}