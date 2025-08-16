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
    int resultLeft = SafeModulo(id - 2, 5);
    int resultRight = SafeModulo(id - 1, 5);
    playerStatusPanelA = new StatusPanel(handlerPanel,wxPoint(0,0),wxSize(200,100),std::to_string(resultLeft));
    playerStatusPanelA->SetId(resultLeft);
    playerACards = new PlayerCardsPanel(handlerPanel,wxPoint(0,60),wxSize(200,126));
    playerStatusPanelB = new StatusPanel(handlerPanel,wxPoint(125,340),wxSize(200,100),std::to_string(resultRight));
    playerBCards = new PlayerCardsPanel(handlerPanel,wxPoint(123,248),wxSize(200,126));
    playerStatusPanelB->SetId(resultRight);
    auto playerStatusPanelACasted = dynamic_cast<StatusPanel*>(playerStatusPanelA);
    auto playerStatusPanelBCasted = dynamic_cast<StatusPanel*>(playerStatusPanelB);
    playerStatusPanelACasted->SetCardsPanel(playerACards);
    playerStatusPanelBCasted->SetCardsPanel(playerBCards);
    AddStatusPanelToEffectManager(playerStatusPanelA);
    AddStatusPanelToEffectManager(playerStatusPanelB);
}