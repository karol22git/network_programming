#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <chrono>
#include <thread>
using boost::asio::ip::tcp;

void handlerr() {
    
}

std::string padd_with_zeros(int how_many, std::string word) {
    std::string zeros = "0";
    for(int i = 1 ; i<how_many ; ++i) {
        zeros.append("0");
    }
    return zeros.append(word);
}
int main(int argc, char* argv[]) {

    if(argc != 3) {
        std::cerr<<"Usage: "<< argv[0] << "<host> <port>" << std::endl;
        return 1;
    }
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(tcp::v4(), argv[1],argv[2]);
        tcp::socket socket(io_context);
        boost::asio::connect(socket,endpoints);

        std::array<char,128> buf;
        boost::system::error_code error;
        size_t len;
        len = socket.read_some(boost::asio::buffer(buf),error);
        if(error == boost::asio::error::eof) {
            return 0;
        }
        else if (error) {
            throw boost::system::system_error(error);
            std::cout.write(buf.data(),len);
        }
        std::cout.write(buf.data(),len);
        std::cout << std::endl;
        boost::asio::write(socket,boost::asio::buffer("1111",5),error);
        for(;;) {
            std::string msg;
            std::cout<<"enter messge: ";
            std::getline(std::cin,msg);
            std::string message_length = std::to_string(msg.length());
            std::cout<<"Header size i write: "<<padd_with_zeros(5 - message_length.length(),message_length)<<std::endl;
            boost::asio::write(socket,boost::asio::buffer(padd_with_zeros(5 - message_length.length(),message_length),5),error);
            std::cout<<"Message i write is:" << msg<<std::endl;
            boost::asio::write(socket,boost::asio::buffer(msg,msg.length()),error);
        }
    }
    catch(std::exception &e) {
        std::cerr<<e.what()<<std::endl;
    }

    return 0;
}