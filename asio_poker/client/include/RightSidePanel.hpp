#pragma once
#include "SidePanel.hpp"

class RightSidePanel: public SidePanel {
    public:
        RightSidePanel(wxWindow*, wxSize);
        void ArrangePanel() override;
};