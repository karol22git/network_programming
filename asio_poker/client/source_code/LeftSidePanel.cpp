#include "../include/LeftSidePanel.hpp"


LeftSidePanel::LeftSidePanel(wxWindow* parent, wxSize size): SidePanel(parent, size) {
    ArrangePanel();
}

void LeftSidePanel::ArrangePanel() {
    playerStatusPanelA = new StatusPanel(handlerPanel,wxSize(200,100),wxPoint(0,0));
    playerStatusPanelB = new StatusPanel(handlerPanel,wxSize(200,100),wxPoint(125,340));
}