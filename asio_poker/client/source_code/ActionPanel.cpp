#include "../include/ActionPanel.hpp"

ActionPanel::ActionPanel(wxWindow* parent, wxSize size) : wxPanel(parent,wxID_ANY,wxPoint(0,0),size) {
    CreateButtons();
    CreateInfoField();
    ArrangeSizer();
    SetSizerAndFit(actionPanelSizer);
}

void ActionPanel::CreateButtons() {
    passButton = new wxButton(this, wxID_ANY, "Pass",wxDefaultPosition,wxSize(150,50));
    raiseButton = new wxButton(this, wxID_ANY, "Raise",wxDefaultPosition,wxSize(150,50));
    //textCtrl = new wxTextCtrl(panel, wxID_ANY);
    //wxBoxSizer* miniSizer = new wxBoxSizer(wxVERTICAL);
    //miniSizer->Add(textCtrl);
    //miniSizer->Add(raiseButton);
    callButton = new wxButton(this, wxID_ANY, "Call",wxDefaultPosition,wxSize(150,50));
}

void ActionPanel::CreateInfoField() {
    //infoField = new wxStaticText(this,wxID_ANY,"  Youre turn! ",wxDefaultPosition,drawButton->GetSize(),wxALIGN_CENTER_HORIZONTAL |wxALIGN_CENTER_VERTICAL );
    //infoField->SetBackgroundStyle(wxBG_STYLE_COLOUR);
    //infoField->SetBackgroundColour(*wxRED);
}

void ActionPanel::ArrangeSizer() {
    actionPanelSizer =  new wxStaticBoxSizer(wxHORIZONTAL,this, "Actions");
    actionPanelSizer->Add(passButton,0,wxALL,10);
    wxTextCtrl* textCtrl = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition, wxSize(150,20));
    wxBoxSizer* miniSizer = new wxBoxSizer(wxVERTICAL);
    miniSizer->Add(textCtrl);
    miniSizer->Add(raiseButton);
    actionPanelSizer->Add(miniSizer,0,wxALL,10);
    actionPanelSizer->Add(callButton,0,wxALL,10);
}

