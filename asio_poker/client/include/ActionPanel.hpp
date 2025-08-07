#pragma once
#include <wx/wx.h>
#include "CommunicationHandler.hpp"
class ActionPanel: public wxPanel {
    public:
        ActionPanel(wxWindow* parent, wxSize size);
        wxButton* GetCallButton() const;
        wxButton* GetRaiseButton() const;
        wxButton* GetPassButton() const;
       // void CreateSmallBlindPanel();
       void HideAll();
       void ShowAll();
       void SetUpSmallBlind();
       void HideMiniSizer();
       void test();
    private:
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
        CommunicationHandler* communicationHandler;
};