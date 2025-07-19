#include "../include/Logger.hpp"

Logger::Logger() {

}

void Logger::AcceptNewConnection(unsigned short port, std::string ip, unsigned int id) {
    std::cout<<"[LOG] accepted new connection. Ip: "<<ip<<", port: "<<port<<", and id: "<<id<<std::endl;
}

void Logger::Message(std::string ip, unsigned short port, std::string& msg) {
    std::cout<<"[LOG] i received message from ip: "<<ip<<" and port: "<<port<<" message: "<<msg<<std::endl;
}