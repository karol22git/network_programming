#include <iostream>
#include <string>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr<< "Usage: " <<argv[0] << "<port>" <<std::endl;
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
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(),port));
        std::string message = "hello";
        boost::system::error_code ignored_error;
        tcp::socket socket(io_context);
        acceptor.accept(socket);
        for(;;) {
            //std::cin>>message;
            //std::cout<<"I read :" <<message << std::endl;
            //std::getline(std::cin,message);
            boost::asio::write(socket, boost::asio::buffer(message),ignored_error);
            break;
        }

    }
    catch (std::exception &e) {
        std::cerr<<e.what()<<std::endl;
    }

    return 0;
}