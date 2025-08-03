#include "../include/ActionPanel.hpp"
#include "../include/Mediator.hpp"
ActionPanel::ActionPanel(wxWindow* parent, wxSize size) : wxPanel(parent,wxID_ANY,wxPoint(0,0),size) {
    CreateButtons();
    CreateInfoField();
    ArrangeSizer();
    SetSizerAndFit(actionPanelSizer);
    callButton->Bind(wxEVT_BUTTON, &CommunicationHandler::SendAnyAction, communicationHandler);
    Mediator::GetInstance().SetActionPanel(this);
}

void ActionPanel::CreateButtons() {
    passButton = new wxButton(this, wxID_ANY, "Pass",wxDefaultPosition,wxSize(150,50));
    raiseButton = new wxButton(this, wxID_ANY, "Raise",wxDefaultPosition,wxSize(150,50));
    callButton = new wxButton(this, wxID_ANY, "Call",wxDefaultPosition,wxSize(150,50));
}

void ActionPanel::CreateInfoField() {
    textCtrl = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition, wxSize(150,20));
}

void ActionPanel::ArrangeSizer() {
    actionPanelSizer =  new wxStaticBoxSizer(wxHORIZONTAL,this, "Actions");
    miniSizer = new wxBoxSizer(wxVERTICAL);
    actionPanelSizer->Add(passButton,0,wxALL,10);
    miniSizer->Add(textCtrl);
    miniSizer->Add(raiseButton);
    actionPanelSizer->Add(miniSizer,0,wxALL,10);
    actionPanelSizer->Add(callButton,0,wxALL,10);
}


wxButton* ActionPanel::GetCallButton() const {
    return callButton;
}

wxButton* ActionPanel::GetRaiseButton() const {
    return raiseButton;
}

wxButton* ActionPanel::GetPassButton() const {
    return passButton;
}