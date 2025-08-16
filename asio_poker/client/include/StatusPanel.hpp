#pragma once
#include <wx/wx.h>
#include "InfoPanel.hpp"
#include "PlayerCardsPanel.hpp"
class StatusPanel: public InfoPanel{//public wxPanel {
    public:
        StatusPanel(wxWindow* parent, wxPoint pos, wxSize size, const std::string&);
        void Arrange() override;
        void CreateItems(const std::string&) override;
        void SetCardsPanel(PlayerCardsPanel* _cardsPanel);
        void SetCards(std::array<struct Card, pocket_cards>&);

        void SetCards(struct Card&, struct Card&);
    private:
        wxStaticText* statusLabel;
        wxStaticText* status;
        PlayerCardsPanel* cardsPanel;
};