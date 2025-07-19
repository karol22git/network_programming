#pragma once
#include <iostream>
#include <string>
class Logger {
    public:
        Logger();
        void AcceptNewConnection(unsigned short port, std::string ip, unsigned int id);
        void Message(std:: string, unsigned short, std::string&);
        
    private:
        std::string newConnection = "new player connected";

};