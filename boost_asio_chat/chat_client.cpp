#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


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
        std::cout<<1<<std::endl;
        for(;;) {
            len = socket.read_some(boost::asio::buffer(buf),error);
            if(error == boost::asio::error::eof) {
                break;
            }
            else if (error) {
                throw boost::system::system_error(error);
                std::cout.write(buf.data(),len);
            }
            //std::cout.write(buf.data(),len);
            std::cout<<"siema";
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}