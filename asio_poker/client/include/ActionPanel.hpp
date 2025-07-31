#pragma once
#include <wx/wx.h>

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
};