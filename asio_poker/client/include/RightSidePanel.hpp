#pragma once
#include "SidePanel.hpp"

class RightSidePanel: public SidePanel {
    public:
        RightSidePanel(wxWindow*, wxSize);
        void ArrangePanel() override;
    private:
        wxPoint playerStatusAPanelPosition = wxPoint(0,340);
        wxPoint playerStatusBPanelPosition = wxPoint(125,0);
        wxPoint playerASubpanelPoistion = wxPoint(0,247);
        wxPoint playerBSubpanelPosition = wxPoint(125,60);
};