#pragma once
#include <wx/wx.h>
#include "../../server/include/Constants.hpp"
class BlindStakePanel: public wxPanel {
    public:
        BlindStakePanel(wxWindow* parent, bool type);
        void GenerateSmallBlindPanel();
        void GenerateBigBlindPanel();
        void Arrange();
        wxButton* GetBlindButton();
    private:
        wxPanel* placeholder;
        wxBoxSizer* sizer;
        wxStaticText* label;
        wxTextCtrl* stake;
        wxButton* blindButton;

        const int margin = 20;
        const unsigned int buttonWidth = 150;
        const unsigned int buttonHeight = 50;
        const unsigned int labelWidth = 30;
        const unsigned int labelHeight = 30;
        const unsigned int stakeWidth = 50;
        const unsigned int stakeheight = 20;
        const unsigned int placeholderWidth = 135;
        const unsigned int placeholderHeight = 50;
        const std::string labelString = "stake:";
        const std::string smallBlind = "small blind";
        const std::string bigBlind = "big blind";
        const std::string smallBlindString = std::to_string(small_blind);
        const std::string bigBlindString = std::to_string(big_blind);
};