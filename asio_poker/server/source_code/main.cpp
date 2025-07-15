//include "Udp_server.hpp"
#include "../include/UdpServer.hpp"
#include <iostream>
#include <string>
int main()
{
  try
  {
    boost::asio::io_context io_context;
    //Udp_server server(io_context);
    UdpServer server(io_context);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}