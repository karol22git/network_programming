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

        const std::string title = "Attention.";
        const std::string buttonLabel = "Exit";
        const unsigned int margin = 10;
        const unsigned int dialogWidth = 300;
        const unsigned int dialogHeight = 150;
};