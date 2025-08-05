#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include "Logger.hpp"
#include "Constants.hpp"
#include <set>
#include <map>
#include "Moderator.hpp"
#include "CommunicationHandler.hpp"
#include <memory>
using boost::asio::ip::udp;

struct TransferredMessageData {
    size_t bytes_transferred;
    std::array<char, 128> recv_buffer_;
};

struct endpoint {
    unsigned short port;
    std::string ip;
    unsigned int id;
    udp::endpoint remote_endpoint;
    endpoint(unsigned short _port, std::string _ip, unsigned int _id, udp::endpoint _remote_endpoint):
        port(_port), ip(_ip), id(_id), remote_endpoint(_remote_endpoint) {}
    
    endpoint(): port(0), ip(""), id(0),
        remote_endpoint(boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), 0)) {}

    bool operator<(const struct endpoint& other) const {
        return id < other.id;
    }
};


class UdpServer {
    public:
        UdpServer(boost::asio::io_context &io_context);
        bool isNewPlayerTryingToConnect(const std::array<char,128>& msg) const;
        void BroadcastTurn();
        void BroadcastMessage(const std::string& msg);
    private:
        void SendMessage(const std::string&);
        void SendMessage(const std::string&, udp::endpoint);
        void HandleNewConnection();
        void RefuseConnection();
        void start_receive();
        void handle_receive(const boost::system::error_code& error,std::size_t /*bytes_transferred*/);
        //void handle_send(std::string /*message*/,const boost::system::error_code& /*error*/,std::size_t /*bytes_transferred*/);
        void handle_send(std::shared_ptr<std::string> message, const boost::system::error_code& error,std::size_t bytes_transferred) ;
        bool CheckForQuorum() const;
        void StartGame();
        void SendPocketCards();
        void SendFlop();
        void AcceptConnection();
        //void BroadcastTurn();
        udp::socket socket_;
        udp::endpoint remote_endpoint_;
        std::array<char, 128> recv_buffer_;
        Logger* logger = nullptr;
        //std::string im = "gwn";
        unsigned int nextID = 0;
        struct Messages infoMessages;
        struct TransferredMessageData mData;
        //std::set<struct endpoint> players;
        std::map<int, struct endpoint> players;
        Moderator* moderator;
        CommunicationHandler* communicationHandler;
};