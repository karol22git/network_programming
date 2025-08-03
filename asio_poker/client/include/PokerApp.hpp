#pragma once
#include <wx/wx.h>
#include "UdpClient.hpp"
#include <memory>
#include <thread>
#include "../include/ClientFrame.hpp"
#include "Mediator.hpp"
class PokerApp: public wxApp{
    public:
        bool OnInit() override;
        void RunClient();
        int OnExit() override;
        ~PokerApp() {
            io_context.stop();
            if (network_thread.joinable()) {
        network_thread.join();
        }
    }
    private:
        ClientFrame* appFrame;
        boost::asio::io_context io_context;
        std::shared_ptr<UdpClient> player;
        std::thread network_thread;
        Mediator* mediator;
};