#include "../include/PokerApp.hpp"
#include "../include/ClientFrame.hpp"
bool PokerApp::OnInit() {
    //moderator->GetGraphicsResources();
    wxInitAllImageHandlers();
    ClientFrame* appFrame = new ClientFrame();
    appFrame->Show(); 
    return true;
}

