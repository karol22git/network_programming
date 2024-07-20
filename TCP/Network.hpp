#pragma once
#include <utility>
#include <list>
#include <memory>
#include "Datagram.hpp"
class host;

class Network {
    public:
        Network(Network&) = delete;
        Network(){};
        static std::shared_ptr<Network> GetInstance();
        void Post(struct Datagram);
        struct Datagram Fetch(std::string);
        //std::string Fetch(std::string);
    private:
        std::shared_ptr<Header> ParseDatagram(std::string);
        std::list<struct Datagram> bytestream;
        static std::shared_ptr<Network> network_;// = nullptr;
};