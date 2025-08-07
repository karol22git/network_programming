#include "../include/ActionPanel.hpp"
#include "../include/Mediator.hpp"
#include "../../server/include/Constants.hpp"
#include <wx/utils.h>
#include <wx/thread.h>
ActionPanel::ActionPanel(wxWindow* parent, wxSize size) : wxPanel(parent,wxID_ANY,wxPoint(0,0),size) {
    CreateButtons();
    CreateInfoField();
    ArrangeSizer();
    SetSizerAndFit(actionPanelSizer);
    callButton->Bind(wxEVT_BUTTON, &CommunicationHandler::SendAnyAction, communicationHandler);
    Mediator::GetInstance().SetActionPanel(this);
    placeholder = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(50,50));
    placeholder->Hide();
    //SetUpSmallBlind();
}

void ActionPanel::CreateButtons() {
    passButton = new wxButton(this, wxID_ANY, "Pass",wxDefaultPosition,wxSize(150,50));
    raiseButton = new wxButton(this, wxID_ANY, "Raise",wxDefaultPosition,wxSize(150,50));
    callButton = new wxButton(this, wxID_ANY, "Call",wxDefaultPosition,wxSize(150,50));
    blindButton = new wxButton(this, wxID_ANY, "small blind",wxDefaultPosition,wxSize(150,50));
    blindButton->Hide();
}

void ActionPanel::CreateInfoField() {
    textCtrl = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition, wxSize(150,20));
    //blindInfoField = new wxStaticText(this, wxID_ANY, std::to_string(small_blind), wxDefaultPosition, wxSize(60, 30), wxST_NO_AUTORESIZE);
    blindTextCtrl = new wxTextCtrl(this, wxID_ANY, "ssss", wxDefaultPosition, wxSize(50, 30), wxTE_READONLY);
    blindTextCtrl->Hide();
    blindLabel  = new wxStaticText(this, wxID_ANY, "stake: ",wxDefaultPosition, wxSize(20,30));
    blindLabel->Hide();
   //blindInfoField->Hide();
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

void ActionPanel::HideAll() {
    actionPanelSizer->ShowItems(false);
}

void ActionPanel::ShowAll() {
    actionPanelSizer->ShowItems(true);
}

void ActionPanel::SetUpSmallBlind() {
    actionPanelSizer->Detach(callButton);
    HideMiniSizer();
    actionPanelSizer->Detach(passButton);
    callButton->Hide();
    passButton->Hide();
    actionPanelSizer->Detach(miniSizer);
    //blindButton = new wxButton(this, wxID_ANY, "small blind",wxDefaultPosition,wxSize(150,50));
    //blindInfoField = new wxStaticText(this, wxID_ANY, std::to_string(small_blind), wxDefaultPosition, wxSize(5, 30), wxST_NO_AUTORESIZE);
    //actionPanelSizer->Add(blindButton);
    //actionPanelSizer->Add(blindInfoField);
    //Layout();
    //placeholder->Show();
    blindButton->Show();
    blindLabel->Show();
    blindTextCtrl->Show();
    placeholder->Show();
    //actionPanelSizer->Add(placeholder,0,wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    actionPanelSizer->Add(blindButton, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    actionPanelSizer->Add(blindLabel,1 , wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    actionPanelSizer->Add(blindTextCtrl, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    actionPanelSizer->Add(placeholder, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    Layout();

}

void ActionPanel::HideMiniSizer() {
    miniSizer->Detach(raiseButton);
    miniSizer->Detach(textCtrl);
    raiseButton->Hide();
    textCtrl->Hide();
}
