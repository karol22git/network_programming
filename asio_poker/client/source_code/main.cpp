#include "../include/UdpClient.hpp"
#include "../include/PokerApp.hpp"
#include <iostream>
#include <string>

wxIMPLEMENT_APP(PokerApp);
//int main(int argc, char* argv[]) {
//    const std::string username = "johny";
//    const std::string password = "123";
//
//try {
//    boost::asio::io_context io_context;
//    std::string ip = "127.0.0.1";
//    std::string port = "8080";
//    //UdpClient* player = new UdpClient(ip, port, io_context);
//    UdpClient player(ip, port, io_context);
//    if(player.Connect(username, password)) {
//      std::cout<<"sukces"<<std::endl;
//      //player->start_receive();
//      io_context.run();
//    }
//    else {
//      std::cout<<"porazka"<<std::endl;
//    }
//    std::cout<<"elo"<<std::endl;
//}
//catch (std::exception& e) {
//  std::cerr << e.what() << std::endl;
//}
//  return 0;
//}