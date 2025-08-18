#pragma once
#include <wx/wx.h>
#include "StatusPanel.hpp"
#include "LeftSidePanel.hpp"
#include "RightSidePanel.hpp"
#include "DrawingCanvas.hpp"
#include "GameStage.hpp"
class GamePanel: public wxPanel {
    public:
        GamePanel(wxWindow* parent);
        void CreateItems();
        void ArrangeItems();
    private:
        DrawingCanvas* gameWindow;
        GameStage* mainGameStage;
        wxBoxSizer* mainSizer;
        wxBoxSizer* middleSizer;
        const wxSize sidePanelSize;
        const int margin = 5;
        SidePanel* leftPanel;
        SidePanel* rightPanel;
};  