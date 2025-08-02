#include "../include/LeftSidePanel.hpp"
#include "../include/Player.hpp"
#include "../include/UdpClient.hpp"
LeftSidePanel::LeftSidePanel(wxWindow* parent, wxSize size): SidePanel(parent, size) {
    ArrangePanel();
}
int SafeModulo(int value, int base) {
    return ((value % base) + base) % base;
}

void LeftSidePanel::ArrangePanel() {
    int id = static_cast<int>(Player::GetInstance().GetId());
int resultLeft = SafeModulo(id - 2, 5);
int resultRight = SafeModulo(id - 1, 5);

    //int resultLeft = (Player::GetInstance().GetId() - 2) % 5;
    //int resultRight = (Player::GetInstance().GetId() - 1) % 5 ;
    ////if(resultLeft<0) {
    ////    resultLeft +=5;
    ////}
    ////if(resultRight<0) {
    ////    resultRight +=5;
    ////}
    ////UdpClient::debugConsole->LogMessage(std::to_string(resultRight));
    ////UdpClient::debugConsole->LogMessage(std::to_string(resultLeft));
    //resultLeft = -100;
    //if(resultRight == 0) resultRight = -200;
    playerStatusPanelA = new StatusPanel(handlerPanel,wxPoint(0,0),wxSize(200,100),std::to_string(resultLeft));
    playerStatusPanelB = new StatusPanel(handlerPanel,wxPoint(125,340),wxSize(200,100),std::to_string(resultRight));

    AddStatusPanelToEffectManager(playerStatusPanelA);
    AddStatusPanelToEffectManager(playerStatusPanelB);
}