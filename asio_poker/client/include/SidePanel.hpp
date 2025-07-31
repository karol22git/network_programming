#pragma once
#include <wx/wx.h>
#include "StatusPanel.hpp"

class SidePanel: public wxPanel {
    public:
        SidePanel(wxWindow*, wxSize);
        virtual void ArrangePanel() = 0;
    protected:
        wxWindow* parent;
        wxSize size;
        StatusPanel* playerStatusPanelA;
        StatusPanel* playerStatusPanelB;
        wxPanel *handlerPanel;
};
