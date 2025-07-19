#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include "Logger.hpp"
#include "Constants.hpp"
#include <set>
using boost::asio::ip::udp;

struct TransferredMessageData {
    size_t bytes_transferred;
    std::array<char, 128> recv_buffer_;
};

struct endpoint {
    unsigned short port;
    std::string ip;
    unsigned int id;
    endpoint(unsigned short _port, std::string _ip, unsigned int _id):
        port(_port), ip(_ip), id(_id) {}
        
    bool operator<(const struct endpoint& other) const {
        return id < other.id;
    }

};
class UdpServer {
    public:
        UdpServer(boost::asio::io_context &io_context);
        //bool isNewPlayerTryingToConnect(const std::string&);const std::array<char,128>& msg
        bool isNewPlayerTryingToConnect(const std::array<char,128>& msg);
    private:
        void SendMessage(const std::string&);
        void HandleNewConnection();
        void RefuseConnection();
        void start_receive();
        void handle_receive(const boost::system::error_code& error,std::size_t /*bytes_transferred*/);
        void handle_send(std::string /*message*/,
            const boost::system::error_code& /*error*/,
            std::size_t /*bytes_transferred*/);
        void AcceptConnection();
        udp::socket socket_;
        udp::endpoint remote_endpoint_;
        std::array<char, 128> recv_buffer_;
        Logger* logger = nullptr;
        std::string im = "gwn";
        unsigned int nextID = 0;
        struct Messages infoMessages;
        struct TransferredMessageData mData;
        std::set<struct endpoint> players;
};