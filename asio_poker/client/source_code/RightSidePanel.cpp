#include "../include/RightSidePanel.hpp"


RightSidePanel::RightSidePanel(wxWindow* parent, wxSize size): SidePanel(parent, size) {
    ArrangePanel();
}

void RightSidePanel::ArrangePanel() {
    playerStatusPanelA = new StatusPanel(handlerPanel,wxSize(200,100),wxPoint(0,340));
    playerStatusPanelB = new StatusPanel(handlerPanel,wxSize(200,100),wxPoint(125,0));
}