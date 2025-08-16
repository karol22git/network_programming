#include "../include/UdpClient.hpp"
#include "../include/DebugConsole.hpp"
#include <iostream>
#include <array>
#include <algorithm>
#include <thread>
#include <chrono>
DebugConsole* UdpClient::debugConsole = nullptr;
UdpClient::UdpClient(const std::string& ip, const std::string& port, boost::asio::io_context &io_context):resolver_(io_context), socket_(io_context),
 messagesHandler(new MessagesHandler()) {
        receiver_endpoint = *resolver_.resolve(udp::v4(),ip,port).begin();
        socket_.open(udp::v4());
}

bool UdpClient::Connect(const std::string& username, const std::string& password) {
    auto message = "[CONNECTION]{{username: " + username + "}, {password: " + password+ "}}";
    socket_.send_to(boost::asio::buffer(message), receiver_endpoint);
    std::array<char, 128> recv_buf;
    size_t len = socket_.receive_from(
        boost::asio::buffer(recv_buf),sender_endpoint);
    //return isConnectionAccepted(recv_buf);
    if(isConnectionAccepted(recv_buf)) {
        std::string msg(recv_buf.data(), len);
        //player = new Player(messagesHandler->ShellId(msg));
        //messagesHandler->SetPlayer(player);
        Player::Init(messagesHandler->ShellId(msg));
        messagesHandler->SetPlayer(&Player::GetInstance());
        start_receive();
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
    socket_.async_receive_from( boost::asio::buffer(recv_buffer_), sender_endpoint,
        std::bind(&UdpClient::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void UdpClient::handle_receive(const boost::system::error_code& error,std::size_t bytes_transferred) {
    //std::cout<<"i got msg"<<std::endl;
    std::string msg(recv_buffer_.data(), bytes_transferred);
    //std::cout<<msg<<std::endl;
    if(debugConsole) debugConsole->LogMessage(msg);
    messagesHandler->ResolveMessage(msg);
    //std::cout << "after resolve" << std::endl;
    start_receive();
}


void UdpClient::SetDebugger(DebugConsole* dc) {
    debugConsole = dc;
    debugConsole->Show();
    messagesHandler->SetDebugger(dc);
}


void UdpClient::SendMessage(const std::string& msg) {
    debugConsole->LogMessage(msg);
    auto msg_ptr = std::make_shared<std::string>(msg);
    socket_.async_send_to(boost::asio::buffer(*msg_ptr),  receiver_endpoint,
        std::bind(&UdpClient::handle_send, this, msg_ptr,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void UdpClient::handle_send(std::shared_ptr<std::string> message, 
    const boost::system::error_code& error,
    std::size_t bytes_transferred) {

}

void UdpClient::SendForcedExitMessage() {
    //const std::string msg = "siema";
    auto id = Player::GetInstance().GetId();
    const std::string msg = forcedExitTemplate + "|" + std::to_string(id)+"|";
    debugConsole->LogMessage(msg);
    socket_.send_to(boost::asio::buffer(msg), receiver_endpoint);
}
