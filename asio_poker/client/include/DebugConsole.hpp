#pragma once
#include <wx/wx.h>
#include <wx/textctrl.h>

class DebugConsole : public wxFrame
{
public:
    DebugConsole(wxWindow* parent);

    void LogMessage(const wxString& msg);

private:
    wxTextCtrl* m_textCtrl;
    
};
