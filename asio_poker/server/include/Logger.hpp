#pragma once
#include <iostream>
#include <string>
class Logger {
    public:
        Logger();
        void AcceptNewConnection(unsigned short port, std::string ip, unsigned int id) const;
        void MessageReceived(std:: string, unsigned short, std::string&) const;
        void MessageSend(std::string ip, unsigned short port,const std::string&) const ;
        
    private:
        std::string newConnection = "new player connected";

};