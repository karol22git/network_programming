#include "../include/RightSidePanel.hpp"
#include "../include/Player.hpp"

RightSidePanel::RightSidePanel(wxWindow* parent, wxSize size): SidePanel(parent, size) {
    ArrangePanel();
}

void RightSidePanel::ArrangePanel() {
    playerStatusPanelA = new StatusPanel(handlerPanel,wxPoint(0,340),wxSize(200,100),std::to_string((Player::GetInstance().GetId() + 1) % 5));
    playerStatusPanelB = new StatusPanel(handlerPanel,wxPoint(125,0),wxSize(200,100),std::to_string((Player::GetInstance().GetId() + 2) % 5));

    AddStatusPanelToEffectManager(playerStatusPanelA);
    AddStatusPanelToEffectManager(playerStatusPanelB);
}