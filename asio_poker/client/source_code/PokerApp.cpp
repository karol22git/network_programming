#include "../include/PokerApp.hpp"
#include "../include/DebugConsole.hpp"

bool PokerApp::OnInit() {
    //moderator->GetGraphicsResources();
    wxInitAllImageHandlers();
    RunClient();
    appFrame = new ClientFrame(this);
    player->SetDebugger(new DebugConsole(appFrame));
    appFrame->Show(); 
    return true;
}

void PokerApp::RunClient() {
    const std::string username = "johny";
    const std::string password = "123";
    try {
       // boost::asio::io_context io_context;
        std::string ip = "127.0.0.1";
        std::string port = "8080";
        //UdpClient* player = new UdpClient(ip, port, io_context);
       // UdpClient player = UdpClient(ip, port, io_context);
        player = std::make_shared<UdpClient>(ip, port, io_context);
        //player->SetDebugger(new DebugConsole(appFrame));
        if(player->Connect(username, password)) {
          std::cout<<"sukces"<<std::endl;
          //player->start_receive();
          //io_context.run();
          
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
    //player->SendForcedExitMessage();
    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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
