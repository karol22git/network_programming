#include "../include/UdpServer.hpp"


UdpServer::UdpServer(boost::asio::io_context &io_context) :socket_(io_context,udp::endpoint(udp::v4(),8080)), logger(new Logger()) {
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
        logger->Message(remote_endpoint_.address().to_string(), remote_endpoint_.port(), std::string(recv_buffer_.data(), bytes_transferred));
        mData.bytes_transferred = bytes_transferred;
        if(isNewPlayerTryingToConnect(recv_buffer_)) {
            HandleNewConnection();
        }
        else {
            socket_.async_send_to(boost::asio::buffer(im), remote_endpoint_,
            std::bind(&UdpServer::handle_send, this, im,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        }
    }
        start_receive();
}

void UdpServer::handle_send(std::string message, 
    const boost::system::error_code& error,
    std::size_t bytes_transferred) {

}

bool UdpServer::isNewPlayerTryingToConnect(const std::array<char,128>& msg) {

    auto head_sequence = infoMessages.CONNECTION_MESSAGE.length();
    auto condition = std::equal(msg.begin(), msg.begin() + head_sequence,
                                infoMessages.CONNECTION_MESSAGE.begin(), infoMessages.CONNECTION_MESSAGE.begin() + head_sequence);
    return condition;
}

void UdpServer::RefuseConnection() {
    SendMessage(infoMessages.REFUSE_CONNECTION);
}

void UdpServer::AcceptConnection() {
    struct endpoint new_player(remote_endpoint_.port(), remote_endpoint_.address().to_string(), nextID);
    logger->AcceptNewConnection(remote_endpoint_.port(), remote_endpoint_.address().to_string(), nextID);
    players.insert(new_player);
    ++nextID;
    SendMessage(infoMessages.ACCEPTED);
}
void UdpServer::HandleNewConnection() {
    nextID < 10 ? AcceptConnection() : RefuseConnection();
}

void UdpServer::SendMessage(const std::string& msg) {
    socket_.async_send_to(boost::asio::buffer(msg), remote_endpoint_,
        std::bind(&UdpServer::handle_send, this, msg,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}