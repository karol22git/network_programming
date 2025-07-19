#include "../include/UdpClient.hpp"
#include <iostream>
#include <array>
#include <algorithm>
UdpClient::UdpClient(const std::string& ip, const std::string& port,  boost::asio::io_context &io_context): resolver_(io_context), socket_(io_context) {
        receiver_endpoint = *resolver_.resolve(udp::v4(),ip,port).begin();
        socket_.open(udp::v4());
        //std::array<char, 1> send_buf  = {{ 0 }};
        //socket_.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
    //    socket_.send_to(boost::asio::buffer(infoMessages.CONNECTION_MESSAGE), receiver_endpoint);
    //    std::array<char, 128> recv_buf;
    //size_t len = socket_.receive_from(
    //    boost::asio::buffer(recv_buf), sender_endpoint);
//
    //std::cout.write(recv_buf.data(), len);
    //std::string s;
    //std::cin>>s;
}

bool UdpClient::Connect(const std::string& username, const std::string& password) {
    auto message = "[CONNECTION]{{username: " + username + "}, {password: " + password+ "}}";
    socket_.send_to(boost::asio::buffer(message), receiver_endpoint);
    //socket_.send_to(boost::asio::buffer(infoMessages.CONNECTION_MESSAGE), receiver_endpoint);
    std::array<char, 128> recv_buf;
    size_t len = socket_.receive_from(
        boost::asio::buffer(recv_buf), sender_endpoint);
    return isConnectionAccepted(recv_buf);
}

bool UdpClient::isConnectionAccepted(const std::array<char,128>& buf) const {
    //for(unsigned int i = 0 ; i < acceptedTemplate.length(); ++i) {
    //    if(buf[i] != acceptedTemplate[i]) return false;
    //}
    //return true;
    return std::equal(acceptedTemplate.begin(), acceptedTemplate.end(), buf.begin());
}

std::string UdpClient::GenerateLogInMessage(const std::string& username, const std::string& password) const{
    return "LOGMSG:{{username:#" + username +"#},{password:#" + password +"#}}";
}