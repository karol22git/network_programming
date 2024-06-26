#include "Network.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <climits>
std::shared_ptr<Network> Network::network_ = nullptr;

std::shared_ptr<Network> Network::GetInstance() {
    if(network_ == nullptr) {
        network_ = std::make_shared<Network>();
    }
    return network_;
}

struct Datagram Network::Fetch(std::string ip) {
    std::filesystem::create_directories("NETWORK/");
    int current_min_sequence_number = INT_MAX;
    std::string current_file = "";
    for(auto& p: std::filesystem::directory_iterator("NETWORK")) {
        std::string file_name = p.path().stem().string(); //.stem().
        int first_occurance_of_ = file_name.find('_');
        std::string sequence_number = file_name.substr(first_occurance_of_ + 1);
        int n = std::stoi(sequence_number);
        if(n < current_min_sequence_number) {
            current_min_sequence_number = n;
            current_file = file_name;
        }
    }

    struct Datagram empty_datagram;
    return empty_datagram;
}

void Network::Post(struct Datagram datagram) {
    std::ofstream NewDatagram("NETWORK/" + datagram.ip +"_" +  std::to_string(datagram.segment.header->GetSequenceNumber()) + ".datagram");
    std::shared_ptr<Header> header = datagram.segment.header;
    _4bits data_offset = header->GetDataOffset();
    _4bits reserved = header->GetReserved();
    _8bits flags  = header->GetFlags();

    NewDatagram << "source port: " << std::to_string(header->GetSourcePort())<<std::endl;
    NewDatagram<< "destination port: " <<std::to_string(header->GetDestinationPort())<<std::endl;
    NewDatagram<< "sequence number: " <<std::to_string(header->GetSequenceNumber())<<std::endl;
    NewDatagram<< "acknowledgment number: " <<std::to_string(header->GetAcknowledgmentNumber())<<std::endl;
    NewDatagram<< "data offset: " << data_offset.a << data_offset.b << data_offset.c <<data_offset.d <<std::endl;
    NewDatagram<< "reserved: " << reserved.a <<reserved.b <<reserved.c << reserved.d <<std::endl;
    NewDatagram << "flags: " << flags.ack << flags.cwr << flags.ece << flags.fin << flags.psh << flags.rst << flags.syn << flags.urg <<std::endl;
    NewDatagram << "window size: " <<header->GetWindowSize()<< std::endl;
    NewDatagram << "checksum: " <<header->GetChecksum() <<std::endl;
    NewDatagram << "urgent pointer: " << header->GetUrgentPointer() << std::endl;
    NewDatagram <<"options: " <<header->GetOptions() << std::endl;

    NewDatagram.close();
    bytestream.push_back(datagram);
    auto s = Fetch(datagram.ip);
}

struct Datagram Network::ParseDatagram(std::string file) {
    std:;shared_ptr<Header> parsed_header = std::make_shared<Header>();
    std::ifstream DatagramFile("NETWORK/" + file + ".datagram");
    std::string text_fetched_from_file;
    int counter = 0;
    while(std::getline(DatagramFile,text_fetched_from_file)) {
        int first_occurance_of_whitespace = file_name.find(' ');
        std::string fetched_value = text_fetched_from_file.substr(first_occurance_of_whitespace +1);
        switch(counter) {
            case 0:
                int source_port = std::stoi(fetched_value);
                parsed_header->SetSourcePort(source_port);
                break;
            case 1:
                int destination_port = std::stoi(fetched_value);
                parsed_header->SetDestinationPort(destination_port);
                break;
            case 2:
                int sequence_number = std::stoi(fetched_value);
                parsed_header->SetSequenceNumber(sequence_number);
                break;
        }
        ++counter;
    }

}
