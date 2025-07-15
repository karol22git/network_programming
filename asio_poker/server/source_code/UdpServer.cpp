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
        std::string s ="ss";
        std::shared_ptr<std::string> ss(new std::string("VERDICT ACCEPTED"));
        //std::shared_ptr<std::string> message(new std::string("succesfully connected")) 
        socket_.async_send_to(boost::asio::buffer(im), remote_endpoint_,
            std::bind(&UdpServer::handle_send, this, im,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        start_receive();
        }
}

void UdpServer::handle_send(std::string message, 
    const boost::system::error_code& error,
    std::size_t bytes_transferred) {

}
