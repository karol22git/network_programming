#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <list>
#include <thread>
#include <chrono>
#include <string>
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
        int id=1;
};

class Chat_room {
    public:
        void join_room(Tcp_Client *c) {
            participants.push_back(c);
            std::string msg;
            start_accepting_messages(c);
        }

        void start_accepting_messages(Tcp_Client *c) {
            std::array<char, 5> header;
            boost::asio::async_read(c->socket(),boost::asio::buffer(header,5),
            boost::bind(&Chat_room::handle_read, this,c,std::ref(header),boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }
        void handle_read(Tcp_Client *c, std::array<char,5> header, const boost::system::error_code& e, size_t s) {
            //std::cout<<"I received B "<<s<<std::endl;//<<msg<<std::endl;
           // if(!e && s>0) {
            int valid = std::atoi(header.data());
            if(!e && valid>0) {
               // std::cout<<"Data on header: "<<header.data()<<std::endl;
               // std::cout.write(header.data(),5);
               const int msg_size = std::atoi(header.data());//std::stoi(header.data());
               std::array<char,64> msg;
              // std::cout<<"Converted header :  "<<std::atoi(header.data())<<std::endl;
                boost::asio::async_read(c->socket(),boost::asio::buffer(msg,msg_size),
                boost::bind(&Chat_room::handle_message,this,c,std::ref(msg),msg_size));
                }
               else {
                    start_accepting_messages(c);
               }
        }
        void handle_message(Tcp_Client *c, std::array<char,64> msg,int msg_size) {
                std::cout.write(msg.data(),msg_size);
                std::cout<<std::endl;
                std::flush(std::cout);
                //std::cout<<"tut"<<std::endl;
                start_accepting_messages(c);
        }

    private:
        std::list<Tcp_Client*> participants;
};
class tcp_server {
    public:
        tcp_server(boost::asio::io_service& io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 4444)), room() {
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
            room.join_room(c);
        }
        start_accept();
    }

    tcp::acceptor acceptor_;
    Chat_room room;
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