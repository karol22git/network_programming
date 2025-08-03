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
    playerStatusPanelB = new StatusPanel(handlerPanel,wxPoint(125,340),wxSize(200,100),std::to_string(resultRight));
    playerStatusPanelB->SetId(resultRight);
    AddStatusPanelToEffectManager(playerStatusPanelA);
    AddStatusPanelToEffectManager(playerStatusPanelB);
}