#pragma once
#include <utility>
#include <list>
#include <memory>
#include "Datagram.hpp"
class host;

class Network {
    public:
        Network(Network&) = delete;
        static std::shared_ptr<Network> GetInstance();
        void Post(struct Datagram);
        void Fetch(std::string);
    private:
        std::list<struct Datagram> bytestream;
        static std::shared_ptr<Network> network_;// = nullptr;
};