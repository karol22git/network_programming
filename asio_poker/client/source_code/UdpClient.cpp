#include "../include/UdpClient.hpp"
#include <iostream>
#include <array>
#include <algorithm>
UdpClient::UdpClient(const std::string& ip, const std::string& port,  boost::asio::io_context &io_context): resolver_(io_context), socket_(io_context) {
        receiver_endpoint = *resolver_.resolve(udp::v4(),ip,port).begin();
        socket_.open(udp::v4());
}

bool UdpClient::Connect(const std::string& username, const std::string& password) {
    auto message = "[CONNECTION]{{username: " + username + "}, {password: " + password+ "}}";
    socket_.send_to(boost::asio::buffer(message), receiver_endpoint);
    std::array<char, 128> recv_buf;
    size_t len = socket_.receive_from(
        boost::asio::buffer(recv_buf), sender_endpoint);
    //return isConnectionAccepted(recv_buf);
    if(isConnectionAccepted(recv_buf)) {
        std::string msg(recv_buf.data(), len);
        player = new Player(messagesHandler->ShellId(msg));
        return true;
    }
    else return false;
}

bool UdpClient::isConnectionAccepted(const std::array<char,128>& buf) const {

    return std::equal(acceptedTemplate.begin(), acceptedTemplate.end(), buf.begin());
}

std::string UdpClient::GenerateLogInMessage(const std::string& username, const std::string& password) const{
    return "LOGMSG:{{username:#" + username +"#},{password:#" + password +"#}}";
}

void UdpClient::start_receive() {
    socket_.async_receive_from( boost::asio::buffer(recv_buffer_), receiver_endpoint,
        std::bind(&UdpClient::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void UdpClient::handle_receive(const boost::system::error_code& error,std::size_t bytes_transferred) {
    std::string msg(recv_buffer_.data(), bytes_transferred);
    std::cout<<msg<<std::endl;
    messagesHandler->ResolveMessage(msg);
    start_receive();
}