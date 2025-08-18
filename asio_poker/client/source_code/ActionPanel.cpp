#include "../include/ActionPanel.hpp"
#include "../include/Mediator.hpp"
#include "../../server/include/Constants.hpp"
#include <wx/utils.h>
#include <wx/thread.h>
ActionPanel::ActionPanel(wxWindow* parent, wxSize size) : wxPanel(parent,wxID_ANY,wxPoint(0,0),size) {
    actionPanelSizer =  new wxStaticBoxSizer(wxHORIZONTAL,this, "Actions");
    miniSizer = new wxBoxSizer(wxVERTICAL);
    CreateButtons();
    CreateInfoField();
    CreateBlindsPanels();
    ArrangeSizer();
    
    SetSizerAndFit(actionPanelSizer);
    callButton->Bind(wxEVT_BUTTON, &CommunicationHandler::SendAnyAction, communicationHandler);
    Mediator::GetInstance().SetActionPanel(this);
    placeholder = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(50,50));
    placeholder->Hide();
    
   //actionPanelSizer->Add(bigBlindStake);
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
    //actionPanelSizer =  new wxStaticBoxSizer(wxHORIZONTAL,this, "Actions");
    //miniSizer = new wxBoxSizer(wxVERTICAL);
    actionPanelSizer->Add(passButton,0,wxALL,10);
    miniSizer->Add(textCtrl);
    miniSizer->Add(raiseButton);
    actionPanelSizer->Add(miniSizer,0,wxALL,10);
    actionPanelSizer->Add(callButton,0,wxALL,10);
    //actionPanelSizer->Add(smallBlindStake,0,wxALL,10);
    //actionPanelSizer->Add(bigBlindStake,0,wxALL,10);
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

std::string ActionPanel::ReadUserInput() {
    return std::string(textCtrl->GetValue());
}

void ActionPanel::HideAll() {
    actionPanelSizer->ShowItems(false);
}

void ActionPanel::ShowAll() {
    callButton->Show();
    passButton->Show();
    raiseButton->Show();
    textCtrl->Show();
}

void ActionPanel::SetUpSmallBlind() {
    HideButtons();
    HideMiniSizer();
    actionPanelSizer->Detach(miniSizer);
    //placeholder->Show();
    smallBlindStake->Show();
    //actionPanelSizer->Add(placeholder,0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    actionPanelSizer->Add(smallBlindStake,1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    Layout();

}

void ActionPanel::SetUpBigBlind() {
    HideButtons();
    HideMiniSizer();
    actionPanelSizer->Detach(miniSizer);
    //placeholder->Show();
    bigBlindStake->Show();
    //actionPanelSizer->Add(placeholder,0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    actionPanelSizer->Add(bigBlindStake,1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    Layout();
}


void ActionPanel::HideMiniSizer() {
    miniSizer->Detach(raiseButton);
    miniSizer->Detach(textCtrl);
    raiseButton->Hide();
    textCtrl->Hide();
}


void ActionPanel::CreateBlindsPanels() {
    bigBlindStake = new BlindStakePanel(this,1);
    smallBlindStake = new BlindStakePanel(this,0);
    bigBlindStake->Hide();
    smallBlindStake->Hide();
}

void ActionPanel::HideButtons() {
    actionPanelSizer->Detach(callButton);
    actionPanelSizer->Detach(passButton);
    callButton->Hide();
    passButton->Hide();
}


wxButton* ActionPanel::GetBigBlindButton() const {
    return bigBlindStake->GetBlindButton();
}

wxButton* ActionPanel::GetSmallBlindButton() const {
    return smallBlindStake->GetBlindButton();
}

void ActionPanel::Rearrange() {
    if(smallBlindStake->IsShown()) {
        actionPanelSizer->Detach(smallBlindStake);
        smallBlindStake->Hide();
    }
    else if(bigBlindStake->IsShown()) {
        actionPanelSizer->Detach(bigBlindStake);
        bigBlindStake->Hide();
    }
    ShowAll();
    ArrangeSizer();
}