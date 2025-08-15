#pragma once
#include <wx/wx.h>
#include "StatusPanel.hpp"
#include "InfoPanel.hpp"
#include "PlayerCardsPanel.hpp"
class SidePanel: public wxPanel {
    public:
        SidePanel(wxWindow*, wxSize);
        virtual void ArrangePanel() = 0;
        void AddStatusPanelToEffectManager(InfoPanel*);
    protected:
        wxWindow* parent;
        wxSize size;
        InfoPanel* playerStatusPanelA;
        InfoPanel* playerStatusPanelB;
        PlayerCardsPanel* playerACards;
        PlayerCardsPanel* playerBCards;
        wxPanel *handlerPanel;
};
