#include <boost/asio.hpp>
#include <iostream>
using boost::asio::ip::udp;
class Udp_server {
    public:
        Udp_server(boost::asio::io_context &io_context) :socket_(io_context,udp::endpoint(udp::v4(),13)) {
            start_receive();
        }
    private:
        void start_receive() {
            socket_.async_receive_from(
                boost::asio::buffer(recv_buffer_), remote_endpoint_,
                std::bind(&Udp_server::handle_receive, this,
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
        }
          void handle_receive(const boost::system::error_code& error,
                std::size_t /*bytes_transferred*/)
            {
                std::cout<<"hello"<<std::endl;
                if(!error) {
std::shared_ptr<std::string> message(
          new std::string("siema"));

      socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
          std::bind(&Udp_server::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

      start_receive();
                }
            }

            void handle_send(std::shared_ptr<std::string> /*message*/,
      const boost::system::error_code& /*error*/,
      std::size_t /*bytes_transferred*/)
  {
  }

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  std::array<char, 1> recv_buffer_;
};