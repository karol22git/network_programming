#include "../include/UdpClient.hpp"

#include <iostream>
#include <string>
int main(int argc, char* argv[]) {
    const std::string username = "johny";
    const std::string password = "123";

try {
    boost::asio::io_context io_context;
    std::string ip = "127.0.0.1";
    std::string port = "8080";
    UdpClient* player = new UdpClient(ip, port, io_context);
    if(player->Connect(username, password)) {
      std::cout<<"sukces"<<std::endl;
    }
    else {
      std::cout<<"porazka"<<std::endl;
    }
    std::string s;
    std::cin>>s;
}
catch (std::exception& e) {
  std::cerr << e.what() << std::endl;
}
  return 0;
}