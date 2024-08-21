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
        std::string FetchDatagramFilename(std::string);
        struct Datagram PrepareDatagram(std::string, std::shared_ptr<Header>);
        void DeleteFromNetwork(std::string);
        std::shared_ptr<Header> ParseDatagram(std::string);
        std::string GetSourceIp(std::string file);
        std::list<struct Datagram> bytestream;
        static std::shared_ptr<Network> network_;// = nullptr;
};