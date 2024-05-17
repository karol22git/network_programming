#include <list>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#if BOOST_VERSION >= 107000
#define GET_IO_SERVICE(s) ((boost::asio::io_context&)(s).get_executor().context())
#else
#define GET_IO_SERVICE(s) ((s).get_io_service())
#endif

#define HEADER_SIZE 5
#define MAX_MESSAGE_SIZE 512
using boost::asio::ip::tcp;
using namespace boost::placeholders;

class Tcp_client {
    public:
        Tcp_client(boost::asio::io_service &io_service) : fd(io_service){}
        tcp::socket& socket() {
            return fd;
        }
    private:
        tcp::socket fd;
};

class Chat_room {
    public:
        void join_room(std::shared_ptr<Tcp_client> client) {
            chat_members.push_back(client);
            start_accepting_messages(client);
        }
        
        void start_accepting_messages(std::shared_ptr<Tcp_client> client) {
            std::array<char,HEADER_SIZE> header;
            boost::asio::async_read(client->socket(), boost::asio::buffer(header, HEADER_SIZE),
            boost::bind(&Chat_room::handle_read, this, client, std::ref(header)));
        }

        void handle_read(std::shared_ptr<Tcp_client> client, std::array<char, HEADER_SIZE> header) {
            int message_size = std::atoi(header.data());
            if ( message_size <= 0 ) {
                start_accepting_messages(client);
                return;
            }
            std::array<char, MAX_MESSAGE_SIZE> message;
            boost::asio::async_read(client->socket(), boost::asio::buffer(message,message_size),
            boost::bind(&Chat_room::handle_message,this,client,std::ref(message),message_size));
        }

        void handle_message(std::shared_ptr<Tcp_client> client, std::array<char, MAX_MESSAGE_SIZE> message, int message_size) {
            std::cout.write(message.data(),message_size);
            std::cout<<std::endl;
            std::flush(std::cout);
            start_accepting_messages(client);
        }

    private:
        std::list<std::shared_ptr<Tcp_client>> chat_members; 
};

class Tcp_server {
    public:
        Tcp_server(boost::asio::io_service &io_service, int port) : acceptor_(io_service, tcp::endpoint(tcp::v4(),port)), room() {
            start_accept();
        }

    private:
        void start_accept() {
            std::shared_ptr<Tcp_client> new_client = std::make_shared<Tcp_client>(GET_IO_SERVICE(acceptor_));
            acceptor_.async_accept(new_client->socket(),
            boost::bind(&Tcp_server::handle_accept,this, new_client,boost::asio::placeholders::error));
        }

        void handle_accept(std::shared_ptr<Tcp_client> client, const boost::system::error_code& e) {
            if(!e) {
                room.join_room(client);
            }
            start_accept();
        }
        tcp::acceptor acceptor_;
        Chat_room room;
};

int main(int argc, char* argv[]) {
    if (argc != 2)
    {
      std::cerr << "Usage: server <host>" << std::endl;
      return 1;
    }
    unsigned int port;
    try {
        port = static_cast<unsigned short>(std::atoi(argv[1]));
    }
    catch (std::exception &e) {
        std::cerr<<"Port have to be positive integer"<<std::endl;
        return 1;
    }
    try {
        boost::asio::io_service io_service;
        Tcp_server server(io_service,port);
        io_service.run();
    }
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}