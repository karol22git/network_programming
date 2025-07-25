#include "../include/PokerApp.hpp"
#include "../include/ClientFrame.hpp"
bool PokerApp::OnInit() {
    //moderator->GetGraphicsResources();
    ClientFrame* appFrame = new ClientFrame();
    appFrame->Show(); 
    return true;
}

