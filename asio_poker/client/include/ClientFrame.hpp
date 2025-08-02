#pragma once
#include <wx/wx.h>
#include "GamePanel.hpp"
#include "ActionPanel.hpp"
#include "StatusBar.hpp"
#include "InfoPanel.hpp"
class ClientFrame: public wxFrame {
    public:
        ClientFrame();
        void CreateItems();
        void ArrangeComponent();
    private:
        const int actionPanelWidth = 800;
        const int actionPanelHeight = 100;
        const int statusBarWidth = 200;
        const int statusBarHeight = 100;
        const int margin = 10;
        wxBoxSizer* mainSizer;
        wxBoxSizer* helperSizer;
        GamePanel* gp;
        ActionPanel* actionPanel;
       // StatusBar* statusBar;
       InfoPanel* statusBar;
};