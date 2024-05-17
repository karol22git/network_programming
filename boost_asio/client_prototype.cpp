
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
//#include "boost/bind.hpp"
using boost::asio::ip::tcp;


void send_message(const boost::system::error_code& errorcode,size_t bytes_transferred, std::string message, int n) {

}

void siema(const boost::system::error_code& errorcode, size_t bytes_transferred) {

}

std::string padding(std::string word, int how_many_zeros) {
    std::string zero = "0";
    for (int i = 1 ; i < how_many_zeros ; ++i) {
        zero.append("0");
    }
    return zero.append(word);
}

void send_header(std::string message,  tcp::socket fd) {
    boost::system::error_code error;
    std::string message_length = std::to_string(message.length());
    std::string header = padding(message_length,5 - message_length.length());
   // boost::asio::write(fd,boost::asio::buffer(message,10),error);
    boost::asio::async_write(fd,boost::asio::buffer(header,header.length()),
   //boost::bind(siema,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
   // boost::bind(&send_message,std::placeholders::_1,std::placeholders::_2)(message,fd));//,
    boost::bind(send_message, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, message, 2));
}

void send_message(std::string message, const tcp::socket &fd) {
   // boost::asio::async_write(fd,boost::asio::buffer(message,message.length()));
}

int main (int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr <<"Usage: "<< argv[0] << "<host> <port>" <<std::endl;
        return 1; 
    }
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(tcp::v4(), argv[1],argv[2]);
        tcp::socket socket(io_context);
        boost::asio::connect(socket,endpoints);


        for(;;) {
            std::string msg;
            std::cout<<"enter messge: ";
            std::getline(std::cin,msg);
            std::string message_length = std::to_string(msg.length());
        }
    }
    catch (std::exception &e) {
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}