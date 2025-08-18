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

        const unsigned int playerStatsPanelWidth = 200;
        const unsigned int playerStatusPanelHeight = 100;
        const unsigned int playerCardsPanelHeight = 126;
        const unsigned int margin = 5;
        const unsigned int step = 1;
};
