#include "../include/Logger.hpp"

Logger::Logger() {

}

void Logger::AcceptNewConnection(unsigned short port, std::string ip, unsigned int id) const {
    std::cout<<"[LOG] accepted new connection. Ip: "<<ip<<", port: "<<port<<", and id: "<<id<<std::endl;
}

void Logger::MessageReceived(std::string ip, unsigned short port, std::string& msg) const {
    std::cout<<"[LOG] i received message from ip: "<<ip<<" and port: "<<port<<" message: "<<msg<<std::endl;
}

void Logger::MessageSend(std::string ip, unsigned short port, const std::string &msg) const {
    std::cout<<"[LOG] i send message to ip: "<<ip<<" and port: "<<port<<" message: "<<msg<<std::endl;
}

void Logger::SimpleLog(const std::string& msg) const {
    std::cout<<msg<<std::endl;
}