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
    auto current_file = FetchDatagramFilename(ip);
    std::shared_ptr<Header> header;
    if(current_file != "") {
        header = ParseDatagram(current_file);
    }
    else {
        header = nullptr;
    }
    struct Datagram fetchedDatagram = PrepareDatagram(ip, header);
    fetchedDatagram.source_ip = GetSourceIp(current_file);
    DeleteFromNetwork(current_file);
    return fetchedDatagram;
}

void Network::Post(struct Datagram datagram) {
    std::string c;
    if(datagram.segment.header->GetSequenceNumber() != 0) {
        c = std::to_string(datagram.segment.header->GetSequenceNumber());
    }
    else {
        c = std::to_string(datagram.segment.header->GetAcknowledgmentNumber());
    }
    std::ofstream NewDatagram("NETWORK/" + datagram.ip +"_" +  c/*std::to_string(datagram.segment.header->GetSequenceNumber()) */+ ".datagram");
    std::shared_ptr<Header> header = datagram.segment.header;
    _4bits data_offset = header->GetDataOffset();
    _4bits reserved = header->GetReserved();
    _8bits flags  = header->GetFlags();
    NewDatagram <<"source_ip: "<< datagram.source_ip<<std::endl;
    NewDatagram << "source_port: " << std::to_string(header->GetSourcePort())<<std::endl;
    NewDatagram<< "destination_port: " <<std::to_string(header->GetDestinationPort())<<std::endl;
    NewDatagram<< "sequence_number: " <<std::to_string(header->GetSequenceNumber())<<std::endl;
    NewDatagram<< "acknowledgment_number: " <<std::to_string(header->GetAcknowledgmentNumber())<<std::endl;
    NewDatagram<< "data_offset: " << data_offset.a << data_offset.b << data_offset.c <<data_offset.d <<std::endl;
    NewDatagram<< "reserved: " << reserved.a <<reserved.b <<reserved.c << reserved.d <<std::endl;
    NewDatagram << "flags: " << flags.cwr << flags.ece << flags.urg << flags.ack << flags.psh << flags.rst << flags.syn << flags.fin <<std::endl;
    NewDatagram << "window_size: " <<header->GetWindowSize()<< std::endl;
    NewDatagram << "checksum: " <<header->GetChecksum() <<std::endl;
    NewDatagram << "urgent_pointer: " << header->GetUrgentPointer() << std::endl;
    NewDatagram <<"options: " <<header->GetOptions() << std::endl;

    NewDatagram.close();
}

std::shared_ptr<Header> Network::ParseDatagram(std::string file) {
    std::shared_ptr<Header> parsed_header = std::make_shared<Header>();
    std::ifstream DatagramFile("NETWORK/" + file + ".datagram");
    std::string text_fetched_from_file;
    int counter = 1;
    std::getline(DatagramFile,text_fetched_from_file);
    while(std::getline(DatagramFile,text_fetched_from_file)) {
        int first_occurance_of_whitespace = text_fetched_from_file.find(' ');
        std::string fetched_value = text_fetched_from_file.substr(first_occurance_of_whitespace +1);
        switch(counter) {
            case 1:
                {
                int source_port = std::stoi(fetched_value);
                parsed_header->SetSourcePort(source_port);
                break;
                }
            case 2:
                {
                int destination_port = std::stoi(fetched_value);
                parsed_header->SetDestinationPort(destination_port);
                break;
                }
            case 3:
            {
                int sequence_number = std::stoi(fetched_value);
                parsed_header->SetSequenceNumber(sequence_number);
                break;
            }
                case 4:
                {
                int acknowledgment_number = std::stoi(fetched_value);
                parsed_header->SetAcknowledgmentNumber(acknowledgment_number);
                break;
                }
            case 5:
            {
                _4bits data_offset;
                fetched_value.at(0) == '0' ? data_offset.a = 0 : data_offset.a = 1;
                fetched_value.at(1) == '0' ? data_offset.b = 0 : data_offset.b = 1;
                fetched_value.at(2) == '0' ? data_offset.c = 0 : data_offset.c = 1;
                fetched_value.at(3) == '0' ? data_offset.d = 0 : data_offset.d = 1;
                parsed_header->SetDataOffset(data_offset);
                break;
            }
            case 6:
            {
                _4bits reserved;
                fetched_value.at(0) == '0' ? reserved.a = 0 : reserved.a = 1;
                fetched_value.at(1) == '0' ? reserved.b = 0 : reserved.b = 1;
                fetched_value.at(2) == '0' ? reserved.c = 0 : reserved.c = 1;
                fetched_value.at(3) == '0' ? reserved.d = 0 : reserved.d = 1;
                parsed_header->SetReserved(reserved);
                break;
            }
            case 7:
            {
                _8bits flags;
                fetched_value.at(0) == '0' ? flags.cwr = 0 : flags.cwr = 1;
                fetched_value.at(1) == '0' ? flags.ece = 0 : flags.ece = 1;
                fetched_value.at(2) == '0' ? flags.urg = 0 : flags.urg = 1;
                fetched_value.at(3) == '0' ? flags.ack = 0 : flags.ack = 1;
                fetched_value.at(4) == '0' ? flags.psh = 0 : flags.psh = 1;
                fetched_value.at(5) == '0' ? flags.rst = 0 : flags.rst = 1;
                fetched_value.at(6) == '0' ? flags.syn = 0 : flags.syn = 1;
                fetched_value.at(7) == '0' ? flags.fin = 0 : flags.fin = 1;
                parsed_header->SetFlags(flags);
                break;
            }
            case 8:
            {
                int window_size = std::stoi(fetched_value);
                parsed_header->SetWindowSize(window_size);
                break;
            }
            case 9:
            {
                int checksum = std::stoi(fetched_value);
                parsed_header->SetChecksum(checksum);
                break;
            }
            case 10:
            {
                int urgent_pointer = std::stoi(fetched_value);
                parsed_header->SetUrgentPointer(urgent_pointer);
                break;
            }
            case 11:
            {
                int options = std::stoi(fetched_value);
                parsed_header->SetOptions(options);
                break;
            }
            default:
                break;
        }
        ++counter;
    }
    return parsed_header;
}


std::string Network::GetSourceIp(std::string file) {
    std::ifstream DatagramFile("NETWORK/" + file + ".datagram");
    std::string text_fetched_from_file;
    std::getline(DatagramFile,text_fetched_from_file);
    int first_occurance_of_whitespace = text_fetched_from_file.find(' ');
    std::string fetched_value = text_fetched_from_file.substr(first_occurance_of_whitespace +1);
    return fetched_value;
}

std::string Network::FetchDatagramFilename(std::string ip) {
    std::filesystem::create_directories("NETWORK/");
    int current_min_sequence_number = INT_MAX;
    std::string current_file = "";
    for(auto& p: std::filesystem::directory_iterator("NETWORK")) {
        std::string file_name = p.path().stem().string(); //.stem().
        int first_occurance_of_ = file_name.find('_');
        std::string sequence_number = file_name.substr(first_occurance_of_ + 1);
        std::string datagram_ip = file_name.substr(0,first_occurance_of_);
        int n = std::stoi(sequence_number);
        if(ip == datagram_ip && n < current_min_sequence_number) {
            current_min_sequence_number = n;
            current_file = file_name;
        }
    }
    return current_file;
}

struct Datagram Network::PrepareDatagram(std::string ip, std::shared_ptr<Header> header) {
    struct Datagram fetchedDatagram;
    struct Segment fetchedSegment;
    fetchedSegment.data = 0;
    fetchedSegment.header = header;
    fetchedDatagram.ip = ip;
    fetchedDatagram.segment = fetchedSegment;
    
    return fetchedDatagram;
}

void Network::DeleteFromNetwork(std::string file_name) {
    if(file_name != "") {
        const std::string file_name_with_extension = "NETWORK/" + file_name + ".datagram";
        std::remove(file_name_with_extension.c_str());
    }
}