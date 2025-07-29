#pragma once
#include <wx/wx.h>
#include "StatusPanel.hpp"
class SidePanel: public wxPanel{
    public:
        SidePanel(wxWindow* parent, wxSize size,bool side);
        void GenerateLeftSidePanel();
        void GenerateRightSidePanel();
    private:
        wxSize size;
};