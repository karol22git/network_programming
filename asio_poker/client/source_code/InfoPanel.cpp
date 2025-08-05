#include "../include/InfoPanel.hpp"


InfoPanel::InfoPanel(wxWindow* parent, wxPoint pos, wxSize size): wxPanel(parent, wxID_ANY, pos, size) {
    SetBackgroundColour(*wxLIGHT_GREY);
}

void InfoPanel::SetStake(const std::string& newStake) {
    stake->SetLabel(newStake);
}

void InfoPanel::SetId(unsigned int _id) {
    id = _id;
}


unsigned int InfoPanel::GetId() const {
    return id;
}