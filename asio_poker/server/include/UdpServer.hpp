#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include "Logger.hpp"
using boost::asio::ip::udp;

class UdpServer {
    public:
        UdpServer(boost::asio::io_context &io_context);
    private:
        void start_receive();
        void handle_receive(const boost::system::error_code& error,std::size_t /*bytes_transferred*/);
        void handle_send(std::string /*message*/,
            const boost::system::error_code& /*error*/,
            std::size_t /*bytes_transferred*/);
        
        udp::socket socket_;
        udp::endpoint remote_endpoint_;
        std::array<char, 1> recv_buffer_;
        Logger* logger = nullptr;
        std::string im = "VERDICT ACCEPTED";
        std::shared_ptr<std::string> imm = std::make_shared<std::string>("succesfully connected");
};