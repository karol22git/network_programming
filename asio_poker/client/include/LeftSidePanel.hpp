#pragma once
#include "SidePanel.hpp"

class LeftSidePanel: public SidePanel {
    public:
        LeftSidePanel(wxWindow*, wxSize);
        void ArrangePanel() override;
};