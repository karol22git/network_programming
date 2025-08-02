#include "../include/DebugConsole.hpp"
#include "../include/Player.hpp"
DebugConsole::DebugConsole(wxWindow* parent)
    : wxFrame(parent, wxID_ANY, "Konsola debugowania", wxDefaultPosition, wxSize(600, 300))
{
    m_textCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                                wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH);
    int resultLeft = (Player::GetInstance().GetId() - 2) % 5;
    int resultRight = (Player::GetInstance().GetId() - 1) % 5 ;
    LogMessage(std::to_string(Player::GetInstance().GetId()));
    LogMessage(std::to_string(resultLeft));
    LogMessage(std::to_string(resultRight));
}

void DebugConsole::LogMessage(const wxString& msg)
{
    m_textCtrl->AppendText(msg + "\n");
}
