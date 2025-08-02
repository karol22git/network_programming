#include "../include/SidePanel.hpp"
#include "../include/EffectManager.hpp"
SidePanel::SidePanel(wxWindow* _parent, wxSize _size) : wxPanel(_parent,wxID_ANY, wxDefaultPosition, _size), 
    handlerPanel(new wxPanel(this,wxID_ANY,wxDefaultPosition, _size)), parent(_parent), size(_size) {
}

void SidePanel::AddStatusPanelToEffectManager(InfoPanel* sp) {
    EffectManager::players.push_back(sp);
}