#include "../include/PokerApp.hpp"
#include "../include/DebugConsole.hpp"
#include "../include/EffectManager.hpp"
bool PokerApp::OnInit() {
    wxInitAllImageHandlers();
    RunClient();
    appFrame = new ClientFrame(this);
    player->SetDebugger(new DebugConsole(appFrame));
    appFrame->Show(); 
    EffectManager::clientFrame = appFrame;
    return true;
}

void PokerApp::RunClient() {
    const std::string username = "johny";
    const std::string password = "123";
    try {
        std::string ip = "127.0.0.1";
        std::string port = "8080";
        player = std::make_shared<UdpClient>(ip, port, io_context);
        if(player->Connect(username, password)) {
          std::cout<<"sukces"<<std::endl;
          
            network_thread = std::thread([this]() {
                try {
                    io_context.run();
                } catch (const std::exception& e) {
                    std::cerr << "Network thread error: " << e.what() << std::endl;
                }
            });
            Mediator::Init();
            Mediator::GetInstance().SetClient(player);

        }
        else {
          std::cout<<"porazka"<<std::endl;
        }
        std::cout<<"elo"<<std::endl;
    }
    catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
}

int PokerApp::OnExit() {
    io_context.stop();
    if (network_thread.joinable()) {
        network_thread.join();
    }
    return wxApp::OnExit();
}


void PokerApp::Shutdown() {
    player->SendForcedExitMessage();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
