#pragma once
#include "SidePanel.hpp"

class LeftSidePanel: public SidePanel {
    public:
        LeftSidePanel(wxWindow*, wxSize);
        void ArrangePanel() override;
    private:
        wxPoint playerAPanelPosition = wxPoint(0,0);
        wxPoint playerBPanelPostiion = wxPoint(125,340);
        wxPoint playerASubpanelPosition = wxPoint(0,60);
        wxPoint playerBSubpanelPosition = wxPoint(123,248);
};