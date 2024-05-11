#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <list>
#include <thread>

#if BOOST_VERSION >= 107000
#define GET_IO_SERVICE(s) ((boost::asio::io_context&)(s).get_executor().context())
#else
#define GET_IO_SERVICE(s) ((s).get_io_service())
#endif


using boost::asio::ip::tcp;

using namespace boost::placeholders;


class Tcp_Client {
    public:
        void handle_write() {
            std::cout<<"I write message to "<<id<<std::endl;
        }
        
        void start() {
            boost::asio::async_write(fd,boost::asio::buffer("Hello from the server!"),
            boost::bind(&Tcp_Client::handle_write,this));
        }
        Tcp_Client(boost::asio::io_service &io_service) : fd(io_service){}

        tcp::socket& socket() {
            return fd;
        }
    private:
        tcp::socket fd;
        int id;
};

class tcp_server {
    public:
        tcp_server(boost::asio::io_service& io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 13)) {
            start_accept();
        }

    
    private:
        void start_accept() {
            Tcp_Client* new_client =new Tcp_Client(GET_IO_SERVICE(acceptor_));
            acceptor_.async_accept(new_client->socket(),
            boost::bind(&tcp_server::handle_accept, this, new_client,
          boost::asio::placeholders::error));
        }

    void handle_accept(Tcp_Client* c, const boost::system::error_code& e) {
        if(!e) {
            c->start();
        }
        start_accept();
    }


    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_service io_service;
        tcp_server server(io_service);
        io_service.run();
    }
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}