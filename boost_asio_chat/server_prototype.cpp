#include <list>
#include <iostream>
#include <string>

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

std::string padding(std::string word, int how_many_zeros) {
    std::string zero = "0";
    for (int i = 1 ; i < how_many_zeros ; ++i) {
        zero.append("0");
    }
    return zero.append(word);
}

class Tcp_client {
    public:
        Tcp_client(boost::asio::io_service &io_service, int i) : fd(io_service){
            id = i;
        }
        tcp::socket& socket() {
            return fd;
        }
        int get_id() {
            return id;
        }

        void send(std::array<char, MAX_MESSAGE_SIZE> m,int ms) {
            message = m;
            message_size = ms;
            std::string header_int = std::to_string(message_size);
            std::string header = padding(header_int,HEADER_SIZE - header_int.length());
            boost::asio::async_write(fd, boost::asio::buffer(header, HEADER_SIZE),
                boost::bind(&Tcp_client::send_body, this/*, message_size*/));
        }
    private:
    void send_body(/*int message_size*/) {
        boost::asio::async_write(fd, boost::asio::buffer(message, message_size),
            boost::bind(&Tcp_client::handler_placeholder, this/*,message_size*/));
    }

    void handler_placeholder(/*int message_size*/) {
    }
        tcp::socket fd;
        std::array<char, MAX_MESSAGE_SIZE> message;
        int message_size;
        int id;
};

class Chat_room {
    public:
        void join_room(std::shared_ptr<Tcp_client> client) {
            start_accepting_messages(client);
            chat_members.push_back(client);
           
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
            send_message(message,message_size, client);
            start_accepting_messages(client);
        }

        void send_message(std::array<char, MAX_MESSAGE_SIZE> message,int message_size, std::shared_ptr<Tcp_client> client) {
            for(auto cm: chat_members) {
                if(cm->get_id() != client->get_id()) {
                    cm->send(message, message_size);
                }
            }
        }
        
        void handler_placeholder() {

        }

        void increment_id() {
            ++next_id;
        }

        int get_next_id() {
            return next_id;
        }

    private:
        std::list<std::shared_ptr<Tcp_client>> chat_members;
        int next_id = 1;
};

class Tcp_server {
    public:
        Tcp_server(boost::asio::io_service &io_service, int port) : acceptor_(io_service, tcp::endpoint(tcp::v4(),port)), room() {
            start_accept();
        }

    private:
        void start_accept() {
            std::shared_ptr<Tcp_client> new_client = std::make_shared<Tcp_client>(GET_IO_SERVICE(acceptor_),room.get_next_id());
            room.increment_id();
            acceptor_.async_accept(new_client->socket(),
            boost::bind(&Tcp_server::handle_accept,this, new_client,boost::asio::placeholders::error));
        }

        void handle_accept(std::shared_ptr<Tcp_client> client, const boost::system::error_code& e) {
            if(!e) {
                room.join_room(client);
                boost::asio::async_write(client->socket(),boost::asio::buffer("hello",5),
                boost::bind(&Tcp_server::handler_placeholder,this));
            }
            start_accept();
        }
        void handler_placeholder() {

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