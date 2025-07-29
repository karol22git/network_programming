#include "../include/GamePanel.hpp"


GamePanel::GamePanel(wxWindow* parent): wxPanel(parent,wxID_ANY,wxPoint(0,0),wxDefaultSize) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* middleSizer = new wxBoxSizer(wxVERTICAL);

    wxSize sidePanelsSize(250,400);

    SidePanel* leftPanel = new SidePanel(this,sidePanelsSize,true);
    wxPanel* panel2 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(350,200));
    panel2->SetBackgroundColour(*wxBLUE);
    SidePanel* rightPanel = new SidePanel(this,sidePanelsSize,false);


    mainSizer->Add(leftPanel, 0, wxEXPAND | wxALL, 5);
    middleSizer->Add(panel2, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(middleSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(rightPanel,0, wxEXPAND | wxALL, 5);
    SetSizerAndFit(mainSizer);
}