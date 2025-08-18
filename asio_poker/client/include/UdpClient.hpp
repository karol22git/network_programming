#pragma once
#include "../../server/include/Constants.hpp"
#include <string>
#include <boost/asio.hpp>
#include <array>
#include "Player.hpp"
#include "MessagesHandler.hpp"
class DebugConsole;
using boost::asio::ip::udp;

class UdpClient{
    public: 
        UdpClient(const std::string& ip,const  std::string& port, boost::asio::io_context& io_context);
        bool Connect(const std::string&, const std::string&);
        bool isConnectionAccepted(const std::array<char,128>&) const;
        std::string GenerateLogInMessage(const std::string& username, const std::string& password) const;
        void start_receive();
        void handle_receive(const boost::system::error_code& error,std::size_t /*bytes_transferred*/);
        static DebugConsole* debugConsole ;
        void SetDebugger(DebugConsole*);
        void SendMessage(const std::string& msg);
        void handle_send(std::shared_ptr<std::string> message, 
            const boost::system::error_code& error,
            std::size_t bytes_transferred);
        void SendForcedExitMessage();
    private:
        std::array<char,128> recv_buffer_;
        udp::resolver resolver_;
        udp::socket socket_;
        udp::endpoint receiver_endpoint;
        udp::endpoint sender_endpoint;
        const std::string acceptedTemplate = "[ACCEPTED]";
        const std::string forcedExitTemplate = "[FORCED]";
        struct Messages infoMessages;
        Player* player;
        MessagesHandler* messagesHandler;
};