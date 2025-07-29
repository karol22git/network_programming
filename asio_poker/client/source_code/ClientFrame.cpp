#include "../include/ClientFrame.hpp"
#include "../include/ActionPanel.hpp"
#include "../include/StatusBar.hpp"
ClientFrame::ClientFrame() :wxFrame(NULL,wxID_ANY,wxString("Poker"),wxDefaultPosition,wxSize(800,400),wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    //wxPanel* panel1 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(800,300));
    GamePanel* gp =  new GamePanel(this);
    ActionPanel* panel2 = new ActionPanel(this,wxSize(800,100));
    //panel1->SetBackgroundColour(*wxRED);     // czerwony
    //panel2->SetBackgroundColour(*wxGREEN);   // zielony
    //mainSizer->Add(panel1,1, wxALL, 10);
    mainSizer->Add(gp,0, wxALL, 10);
    //mainSizer->Add(panel2,0, wxALL, 10);
    //wxPanel* panel3 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(200,100));
    StatusBar* sBar = new StatusBar(this,wxSize(200,100));
    wxBoxSizer* helperSizer = new wxBoxSizer(wxHORIZONTAL);
    helperSizer->Add(sBar,0,wxALL,10);
    helperSizer->Add(panel2,0,wxALL,10);
    mainSizer->Add(helperSizer,0, wxALL, 10);
    SetSizerAndFit(mainSizer);
}