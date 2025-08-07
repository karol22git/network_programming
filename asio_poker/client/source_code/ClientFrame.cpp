#include "../include/ClientFrame.hpp"
#include "../include/ActionPanel.hpp"
#include "../include/StatusBar.hpp"
#include "../include/EffectManager.hpp"
#include "../include/Player.hpp"
#include "../include/PokerApp.hpp"

ClientFrame::ClientFrame(PokerApp * parent) :wxFrame(NULL,wxID_ANY,wxString("Poker"),wxDefaultPosition,wxSize(800,400),wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER), app(parent) {
    CreateItems();
    ArrangeComponent();
    SetSizerAndFit(mainSizer);
    Bind(wxEVT_CLOSE_WINDOW, &ClientFrame::OnClose, this);

}

void ClientFrame::CreateItems() {
    mainSizer = new wxBoxSizer(wxVERTICAL);
    gp =  new GamePanel(this);
    actionPanel = new ActionPanel(this,wxSize(actionPanelWidth,actionPanelHeight));
    statusBar = new StatusBar(this,wxDefaultPosition, wxSize(statusBarWidth,statusBarHeight), "hello");
    statusBar->SetId(Player::GetInstance().GetId());
    helperSizer = new wxBoxSizer(wxHORIZONTAL);
    //bindPanel = new BindPanel(this,wxSize(actionPanelWidth,actionPanelHeight),"small bind","20");
    EffectManager::players.push_back(statusBar);
    EffectManager::actionPanel = actionPanel;
}

void ClientFrame::ArrangeComponent() {
    mainSizer->Add(gp,0, wxALL, margin);
    helperSizer->Add(statusBar,0,wxALL,margin);
    helperSizer->Add(actionPanel,0,wxALL,margin);
    //helperSizer->Add(bindPanel,0,wxALL,margin);
    mainSizer->Add(helperSizer,0, wxALL, margin);
}

void ClientFrame::OnClose(wxCloseEvent& event) {
    app->Shutdown(); // wywołaj własną logikę
    event.Skip();    // pozwól wxWidgets kontynuować zamykanie
}
