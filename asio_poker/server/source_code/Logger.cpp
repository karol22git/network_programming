#include "../include/Logger.hpp"

Logger::Logger() {

}

void Logger::AcceptNewConnection(unsigned short port, std::string ip, unsigned int id) const {
    std::cout<<acceptNewConnectionString<<ip<<", port: "<<port<<", and id: "<<id<<std::endl;
}

void Logger::MessageReceived(std::string ip, unsigned short port, std::string& msg) const {
    std::cout<<messageReceivedString<<ip<<" and port: "<<port<<" message: "<<msg<<std::endl;
}

void Logger::MessageSend(std::string ip, unsigned short port, const std::string &msg) const {
    std::cout<<messageSendString<<ip<<" and port: "<<port<<" message: "<<msg<<std::endl;
}

void Logger::SimpleLog(const std::string& msg) const {
    std::cout<<msg<<std::endl;
}