
#include <iostream>
#include <string>
#include <list>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <utility>
#include <thread>
//#include "boost/bind.hpp"
using boost::asio::ip::tcp;

#define HEADER_SIZE 5
#define MAX_MESSAGE_SIZE 512

std::string padding(std::string word, int how_many_zeros) {
    std::string zero = "0";
    for (int i = 1 ; i < how_many_zeros ; ++i) {
        zero.append("0");
    }
    return zero.append(word);
}

class Client {
    public:
        Client(boost::asio::io_service &io_service, const tcp::resolver::results_type& endpoints) : fd(io_service), io_context_(io_service) {
           // boost::asio::connect(fd,endpoints);
            boost::asio::async_connect(fd,endpoints,
            boost::bind(&Client::start,this));
        }

        
        void start() {
            std::array<char, 5> hello;
            boost::asio::async_read(fd, boost::asio::buffer(hello,5),
            boost::bind(&Client::handshake,this,std::ref(hello)));
            //io_context_.run_one();
        }

        void handshake(std::array<char,5> hello) {
            std::cout.write(hello.data(),5);
            std::cout<<std::endl;
            std::flush(std::cout);
            receive();
        }
        void send_header(std::string message) {
            boost::system::error_code error;
            std::string idk = message;
            std::string message_length = std::to_string(message.length());
            std::string header = padding(message_length,HEADER_SIZE - message_length.length());
           // std::cout<<header<<std::endl;
            boost::asio::async_write(fd,boost::asio::buffer(header,HEADER_SIZE),
            boost::bind(&Client::send_body, this, std::ref(idk)));
            
        io_context_.run_one();
        }
        tcp::socket& socket() {
            return fd;
        }

    private:
        void send_body(std::string message) {
            boost::asio::async_write(fd,boost::asio::buffer(message,message.length()),
            boost::bind(&Client::handler_placeholder, this));
        }

        void handler_placeholder() {
             
        }
        
        void receive() {
            std::array<char, HEADER_SIZE> header;
            boost::asio::async_read(fd,boost::asio::buffer(header, HEADER_SIZE),
            boost::bind(&Client::receive_body,this, std::ref(header)));
        }

        void receive_body(std::array<char, HEADER_SIZE> header) {
            int message_size = std::atoi(header.data());
            std::cout<<message_size<<std::endl;
            std::cout.write(header.data(),HEADER_SIZE);
            std::cout<<std::endl;
            std::flush(std::cout);
            if ( message_size <= 0 ) {
                receive();
               //start();
                return;
            }
            //std::array<char, MAX_MESSAGE_SIZE> message;
            boost::asio::async_read(fd, boost::asio::buffer(message,message_size),
            boost::bind(&Client::handle_message,this/*,message*/,message_size,boost::asio::placeholders::error));
        }

        void handle_message(/*std::array<char, MAX_MESSAGE_SIZE> message*/int message_size, const boost::system::error_code& e) {
            if(!e) {
                std::cout.write(message.data(),message_size);
                std::cout<<std::endl;
                std::flush(std::cout);
            }
            else {
                std::cout<<"error has occured"<<std::endl;
            }
            receive();
           //start();
        }

    tcp::socket fd;
    std::array<char, MAX_MESSAGE_SIZE> message;
    std::list<std::array<char, MAX_MESSAGE_SIZE>> messages;
    boost::asio::io_context& io_context_;
};

int main (int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr <<"Usage: "<< argv[0] << "<host> <port>" <<std::endl;
        return 1; 
    }
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(tcp::v4(), argv[1],argv[2]);
        Client client (io_context,endpoints);
        //client.start();
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> s= boost::asio::make_work_guard(io_context);
        std::thread t([&io_context](){ io_context.run(); });
       // client.start();
        for(;;) {
            std::string msg;
            std::cout<<"enter messge: ";
            std::getline(std::cin,msg);
            client.send_header(msg);
            
        }

    }
    
    catch (std::exception &e) {
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}