#pragma once
#include <wx/wx.h>
#include <string>
class EndGameDialog: public wxDialog {
    public:
        EndGameDialog(wxWindow* parent,std::string info);
    private:
        void OnClose(wxCloseEvent& event);
        void DialogExit(wxCommandEvent &event);
        void DialogContinue(wxCommandEvent &event);
};