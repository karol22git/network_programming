#pragma once
#include <wx/wx.h>
#include "CommunicationHandler.hpp"
#include "BlindStakePanel.hpp"
class ActionPanel: public wxPanel {
    public:
        ActionPanel(wxWindow* parent, wxSize size);
        wxButton* GetCallButton() const;
        wxButton* GetRaiseButton() const;
        wxButton* GetPassButton() const;
        wxButton* GetBigBlindButton() const;
        wxButton* GetSmallBlindButton() const;
       // void CreateSmallBlindPanel();
       void HideAll();
       void ShowAll();
       void SetUpSmallBlind();
       void SetUpBigBlind();
       void HideMiniSizer();
       void Rearrange();
       std::string ReadUserInput();
    private:
        BlindStakePanel* bigBlindStake;
        BlindStakePanel* smallBlindStake;
        wxPanel* placeholder;
        wxTextCtrl* blindTextCtrl;
        wxButton* blindButton;
        wxStaticText* blindInfoField;
        wxStaticText* blindLabel;
        wxBoxSizer* blindSizer;
        wxButton *callButton;
        wxButton *passButton;
        wxButton *raiseButton;
        wxStaticText *infoField;
        wxStaticBoxSizer *actionPanelSizer;
        wxBoxSizer* miniSizer;
        wxTextCtrl* textCtrl;
        void CreateButtons();
        void CreateInfoField();
        void ArrangeSizer();
        void CreateBlindsPanels();
        void HideButtons();
        CommunicationHandler* communicationHandler;
};