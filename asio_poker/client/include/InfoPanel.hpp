#pragma once
#include <wx/wx.h>
#include "../../server/include/Constants.hpp"

class InfoPanel: public wxPanel {
    public:
        InfoPanel(wxWindow* parent, wxPoint pos, wxSize size);
        void SetStake(const std::string&);
        void SetStake(int);
        void SetId(unsigned int);
        unsigned int GetId() const;
        virtual void Arrange() = 0;
        virtual void CreateItems(const std::string&) = 0;
    protected:
        wxGridSizer* grid;
        wxStaticText* nicknameLabel;
        wxStaticText* nickname;
        wxStaticText* stakeLabel;
        wxStaticText* stake;
        unsigned int id;
};