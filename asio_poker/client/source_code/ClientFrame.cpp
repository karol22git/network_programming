#include "../include/ClientFrame.hpp"
#include "../include/ActionPanel.hpp"
#include "../include/StatusBar.hpp"
ClientFrame::ClientFrame() :wxFrame(NULL,wxID_ANY,wxString("Poker"),wxDefaultPosition,wxSize(800,400),wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {
    CreateItems();
    ArrangeComponent();
    SetSizerAndFit(mainSizer);
}

void ClientFrame::CreateItems() {
    mainSizer = new wxBoxSizer(wxVERTICAL);
    gp =  new GamePanel(this);
    actionPanel = new ActionPanel(this,wxSize(actionPanelWidth,actionPanelHeight));
    statusBar = new StatusBar(this,wxSize(statusBarWidth,statusBarHeight));
    helperSizer = new wxBoxSizer(wxHORIZONTAL);
}

void ClientFrame::ArrangeComponent() {
    mainSizer->Add(gp,0, wxALL, margin);
    helperSizer->Add(statusBar,0,wxALL,margin);
    helperSizer->Add(actionPanel,0,wxALL,margin);
    mainSizer->Add(helperSizer,0, wxALL, margin);
}