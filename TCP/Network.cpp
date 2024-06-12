#include "Network.hpp"
#include <iostream>
#include <fstream>

std::shared_ptr<Network> Network::network_ = nullptr;

std::shared_ptr<Network> Network::GetInstance() {
    if(network_ == nullptr) {
        network_ = std::make_shared<Network>();
    }
    return network_;
}

struct Datagram Network::Fetch(std::string ip) {
    for(auto it = bytestream.begin() ; it != bytestream.end() ; ++it) {
        if(it->ip == ip) {
            bytestream.erase(it);
            return *it;
        }
    }
    struct Datagram empty_datagram;
    return empty_datagram;
}

void Network::Post(struct Datagram datagram) {
    std::ofstream NewDatagram("NETWORK/datagram_to_" + datagram.ip +"_" +  std::to_string(datagram.segment.header->GetSequenceNumber()));
    /*Header* header = datagram.segment.header;
    NewDatagram<< std::to_string(header->GetSourcePort())<<std::endl;
    NewDatagram<< std::to_string(header->GetDestinationPort())<<std::endl;
    NewDatagram<< std::to_string(header->GetSequenceNumber())<<std::endl;
    NewDatagram<< std::to_string(header->GetAcknowledgeNumber())<<std::endl;*/
    NewDatagram.close();
    bytestream.push_back(datagram);
}

