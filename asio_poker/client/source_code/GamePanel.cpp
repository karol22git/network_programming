#include "../include/GamePanel.hpp"
#include "../include/EffectManager.hpp"

GamePanel::GamePanel(wxWindow* parent): wxPanel(parent,wxID_ANY,wxPoint(0,0),wxDefaultSize),sidePanelSize(250, 400) {
    CreateItems();
    ArrangeItems();
    SetSizerAndFit(mainSizer);
}

void GamePanel::CreateItems() {
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    middleSizer = new wxBoxSizer(wxVERTICAL);
    leftPanel = new LeftSidePanel(this,sidePanelSize);
    rightPanel = new RightSidePanel(this,sidePanelSize);
    //gameWindow = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(350,200));
    gameWindow = new DrawingCanvas(this,wxID_ANY,wxDefaultPosition,wxSize(350,200));
    EffectManager::drawingCanvas = gameWindow;
}

void GamePanel::ArrangeItems() {
    gameWindow->SetBackgroundColour(*wxGREEN);
    mainSizer->Add(leftPanel, 0, wxEXPAND | wxALL, margin);
    middleSizer->Add(gameWindow, 1, wxEXPAND | wxALL, margin);
    mainSizer->Add(middleSizer, 1, wxEXPAND | wxALL, margin);
    mainSizer->Add(rightPanel,0, wxEXPAND | wxALL, margin);
}