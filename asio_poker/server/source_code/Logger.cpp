#include "../include/Logger.hpp"

Logger::Logger() {

}

void Logger::NewConnection(std::string ip, std::string port) {
    std::cout<<"[LOG] "<<"new connection. Ip: "<<ip<<" ,port: "<<port<<std::endl;
}