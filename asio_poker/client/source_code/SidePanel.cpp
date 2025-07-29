#include "../include/SidePanel.hpp"


SidePanel::SidePanel(wxWindow* parent, wxSize _size,bool side): wxPanel(parent,wxID_ANY,wxPoint(0,0),_size) {
    size = _size;
    if(side) GenerateLeftSidePanel();
    else GenerateRightSidePanel();
}

void SidePanel::GenerateLeftSidePanel() {
    wxPanel *handlerPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition, size);
    StatusPanel* playerStatusPanelA = new StatusPanel(handlerPanel,wxSize(200,100),wxPoint(0,0));
    StatusPanel* playerStatusPanelB = new StatusPanel(handlerPanel,wxSize(200,100),wxPoint(125,340));

    //SetBackgroundColour(*wxGREEN);
}

void SidePanel::GenerateRightSidePanel() {
    wxPanel *handlerPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition, size);   
    StatusPanel* playerStatusPanelA = new StatusPanel(handlerPanel,wxSize(200,100),wxPoint(0,340));
    StatusPanel* playerStatusPanelB = new StatusPanel(handlerPanel,wxSize(200,100),wxPoint(125,0));
    //SetBackgroundColour(*wxGREEN);
}

//250 400