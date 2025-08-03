#pragma once
#include <wx/wx.h>
#include "CommunicationHandler.hpp"
class ActionPanel: public wxPanel {
    public:
        ActionPanel(wxWindow* parent, wxSize size);
    private:
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
        void AnyAction();
        wxButton* GetCallButton() const;
        wxButton* GetRaiseButton() const;
        wxButton* GetPassButton() const;
        CommunicationHandler* communicationHandler;
};