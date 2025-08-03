#include "../include/UdpServer.hpp"

#include <thread>
#include <chrono>

UdpServer::UdpServer(boost::asio::io_context &io_context) :socket_(io_context,udp::endpoint(udp::v4(),8080)), moderator(new Moderator()), logger(new Logger()),
    communicationHandler(new CommunicationHandler) {
    start_receive();
    //logger = new Logger();
}

void UdpServer::start_receive() {
    socket_.async_receive_from( boost::asio::buffer(recv_buffer_), remote_endpoint_,
        std::bind(&UdpServer::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handle_receive(const boost::system::error_code& error,std::size_t bytes_transferred) {
    if(!error) {
        logger->MessageReceived(remote_endpoint_.address().to_string(), remote_endpoint_.port(), std::string(recv_buffer_.data(), bytes_transferred));
        mData.bytes_transferred = bytes_transferred;
        if(isNewPlayerTryingToConnect(recv_buffer_)) {
            HandleNewConnection();
        }
        else {
            auto msg_ptr = std::make_shared<std::string>(im);
            socket_.async_send_to(boost::asio::buffer(*msg_ptr), remote_endpoint_,
            std::bind(&UdpServer::handle_send, this, msg_ptr,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        }
    }
        start_receive();
}

//void UdpServer::handle_send(std::string message, 
//    const boost::system::error_code& error,
//    std::size_t bytes_transferred) {
//
//}

void UdpServer::handle_send(std::shared_ptr<std::string> message, 
    const boost::system::error_code& error,
    std::size_t bytes_transferred) {

}

bool UdpServer::isNewPlayerTryingToConnect(const std::array<char,128>& msg) const {

    auto head_sequence = infoMessages.CONNECTION_MESSAGE.length();
    auto condition = std::equal(msg.begin(), msg.begin() + head_sequence,
                                infoMessages.CONNECTION_MESSAGE.begin(), infoMessages.CONNECTION_MESSAGE.begin() + head_sequence);
    return condition;
}

void UdpServer::RefuseConnection() {
    SendMessage(infoMessages.REFUSE_CONNECTION);
}

void UdpServer::AcceptConnection() {
    struct endpoint new_player(remote_endpoint_.port(), remote_endpoint_.address().to_string(), nextID,remote_endpoint_);
    logger->AcceptNewConnection(remote_endpoint_.port(), remote_endpoint_.address().to_string(), nextID);
    players[new_player.id] = new_player;
    ++nextID;
    SendMessage(infoMessages.ACCEPTED + "{" + std::to_string(new_player.id) +"}");


    moderator->CreateNewPlayer(new_player.id);
    auto condition = CheckForQuorum();
    if(condition) StartGame();
    //moderator->StartGame();
    //auto players = moderator->GetPlayers();
    //auto p = players[0];
    //auto cards = p->GetPocketCards();
    //std::string  s = communicationHandler->GeneratePocketCardsMessage(cards[0],cards[1]);
    //SendMessage(s);
}

void UdpServer::HandleNewConnection() {
    nextID < 10 ? AcceptConnection() : RefuseConnection();
}

void UdpServer::SendMessage(const std::string& msg) {
    logger->MessageSend(remote_endpoint_.address().to_string(), remote_endpoint_.port(), msg);
    auto msg_ptr = std::make_shared<std::string>(msg);
    socket_.async_send_to(boost::asio::buffer(*msg_ptr), remote_endpoint_,
        std::bind(&UdpServer::handle_send, this, msg_ptr,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

bool UdpServer::CheckForQuorum() const {
    if( nextID>= quorum) return true;
    else return false;
}

void UdpServer::StartGame() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    moderator->StartGame();
    SendPocketCards();
   // std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::string msg = "hello";
    //auto msg_ptr = std::make_shared<std::string>(msg);
    //SendMessage("hello");
    SendFlop();
    BroadcastTurn();
}

void UdpServer::SendPocketCards() {
    auto playersList = moderator->GetPlayers();
    for(auto player: playersList) {
        auto cards = player->GetPocketCards();
        std::string  s = communicationHandler->GeneratePocketCardsMessage(cards[0],cards[1]);
        SendMessage(s,players[player->GetId()].remote_endpoint);
    }
}

void UdpServer::SendFlop() {
    auto flop = moderator->GetFlop();
    auto msg = communicationHandler->GenerateFlopMessage(flop[0],flop[1],flop[2]);
    for(const auto& [key, value] : players) {
        SendMessage(msg, value.remote_endpoint);
    }
}

void UdpServer::BroadcastTurn() {
    auto msg = communicationHandler->GenerateTurnMessage(0);
     for(const auto& [key, value] : players) {
        SendMessage(msg, value.remote_endpoint);
    }
}


void UdpServer::SendMessage(const std::string& msg, udp::endpoint endpoint) {
    logger->MessageSend(endpoint.address().to_string(), endpoint.port(), msg);
    auto msg_ptr = std::make_shared<std::string>(msg);
    socket_.async_send_to(boost::asio::buffer(*msg_ptr), endpoint,
        std::bind(&UdpServer::handle_send, this, msg_ptr,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}
