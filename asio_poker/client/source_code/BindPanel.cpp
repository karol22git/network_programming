#include "../include/BindPanel.hpp"

BindPanel::BindPanel(wxWindow* parent, wxSize size,const std::string& title, const std::string& amount): wxPanel(parent,wxID_ANY,wxPoint(0,0),size) {
    CreateItems(title, amount);
    Arrange();
    SetSizerAndFit(bindPanelSizer);
}

void BindPanel::Arrange() {
    bindPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    bindPanelSizer->Add(actionButton);
    bindPanelSizer->Add(infoField);
}

void BindPanel::CreateItems(const std::string& title, const std::string& amount) {
    actionButton = new wxButton(this, wxID_ANY, title, wxDefaultPosition,wxSize(150,50));
    infoField = new wxStaticText(this, wxID_ANY, amount, wxDefaultPosition, wxDefaultSize);
}