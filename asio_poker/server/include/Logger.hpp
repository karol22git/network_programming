#pragma once
#include <iostream>
#include <string>
class Logger {
    public:
        Logger();
        void NewConnection(std::string ip, std::string port);
        
    private:
        std::string newConnection = "new player connected";

};