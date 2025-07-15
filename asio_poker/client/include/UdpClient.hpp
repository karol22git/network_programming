#pragma once
#include <string>
#include <boost/asio.hpp>
#include <array>
using boost::asio::ip::udp;

class UdpClient{
    public:
        UdpClient(const std::string& ip,const  std::string& port, boost::asio::io_context& io_context);
        bool Connect(const std::string&, const std::string&);
        bool isConnectionAccepted(const std::array<char,128>&) const;
        std::string GenerateLogInMessage(const std::string& username, const std::string& password) const;
    private:
        udp::resolver resolver_;
        udp::socket socket_;
        udp::endpoint receiver_endpoint;
        udp::endpoint sender_endpoint;
        const std::string acceptedTemplate = "VERDICT ACCEPTED";
};