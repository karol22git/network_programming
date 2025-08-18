#include "../include/LeftSidePanel.hpp"
#include "../include/Player.hpp"
#include "../include/UdpClient.hpp"
LeftSidePanel::LeftSidePanel(wxWindow* parent, wxSize size): SidePanel(parent, size) {
    ArrangePanel();
}

void LeftSidePanel::ArrangePanel() {
    auto SafeModulo  = [] (int value, int base) {
        return ((value % base) + base) % base;
    };
    int id = static_cast<int>(Player::GetInstance().GetId());
    int resultLeft = SafeModulo(id - 2*step, margin);
    int resultRight = SafeModulo(id - step, margin);
    playerStatusPanelA = new StatusPanel(handlerPanel,playerAPanelPosition,wxSize(playerStatsPanelWidth,playerStatusPanelHeight),std::to_string(resultLeft));
    playerStatusPanelA->SetId(resultLeft);
    playerACards = new PlayerCardsPanel(handlerPanel,playerASubpanelPosition,wxSize(playerStatsPanelWidth,playerCardsPanelHeight));
    playerStatusPanelB = new StatusPanel(handlerPanel,playerBPanelPostiion,wxSize(playerStatsPanelWidth,playerStatusPanelHeight),std::to_string(resultRight));
    playerBCards = new PlayerCardsPanel(handlerPanel,playerBSubpanelPosition,wxSize(playerStatsPanelWidth,playerCardsPanelHeight));
    playerStatusPanelB->SetId(resultRight);
    auto playerStatusPanelACasted = dynamic_cast<StatusPanel*>(playerStatusPanelA);
    auto playerStatusPanelBCasted = dynamic_cast<StatusPanel*>(playerStatusPanelB);
    playerStatusPanelACasted->SetCardsPanel(playerACards);
    playerStatusPanelBCasted->SetCardsPanel(playerBCards);
    AddStatusPanelToEffectManager(playerStatusPanelA);
    AddStatusPanelToEffectManager(playerStatusPanelB);
}