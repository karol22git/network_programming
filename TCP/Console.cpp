#include "Console.hpp"
#include "Host.hpp"
#include <iostream>
Console::Console() {}


void Console::Log(Host* host, struct Datagram datagram) {
    std::cout<<"--------------------------------"<<std::endl;
    PrintState(host);
    PrintSegmentInfo(datagram);
    std::cout<<"--------------------------------"<<std::endl;
}

void Console::PrintState(Host *host) {
    States state = host->GetState();
    std::string string_state;
    switch(state) {
        case 1:
            string_state = "LISTEN";
            break;
        case 2:
            string_state = "SYN_SENT";
            break;
        case 3:
            string_state = "SYN_RECEIVED";
            break;
        case 4:
            string_state = "ESTABLISHED";
            break;
        case 5:
            string_state = "FIN_WAIT_1";
            break;
        case 6:
            string_state = "FIN_WAIT_2";
            break;
        case 7:
            string_state = "CLOSE_WAIT";
            break;
        case 8:
            string_state = "CLOSING";
            break;
        case 9:
            string_state = "LAST_ACK";
            break;
        case 10:
            string_state = "TIME_WAIT";
            break;
        case 11:
            string_state = "CLOSED";
            break;
        default:
            string_state = "UNDEFINED";
            break;
    }
    std::cout<<"Current host state: "<<string_state<<std::endl;
}


void Console::PrintSegmentInfo(struct Datagram datagram) {
    _8bits f = datagram.segment.header->GetFlags();
    std::cout<<"Datagram source ip: "<< datagram.source_ip<<std::endl;
    std::cout<<"Datagram source port: "<<datagram.segment.header->GetSourcePort() <<std::endl;
    std::cout<<"Header type: "<< HeaderTypeToString(datagram.segment.header->GetHeaderType()) <<std::endl;
    std::cout<<"Sequance number: "<< datagram.segment.header->GetSequenceNumber()<<std::endl;
    std::cout<<"Acknowledgement number: "<<datagram.segment.header->GetAcknowledgmentNumber() << std::endl;
    std::cout<<"Flags: "<<f.cwr<< f.ece << f.urg << f.ack << f.psh<<f.rst<<f.syn<<f.fin<< std::endl;
};

std::string Console::HeaderTypeToString(HeaderType hType) {
    std::string result;
    switch(hType) {
        case 1:
            result = "SYN";
            break;
        case 2:
            result = "SYNACK";
            break;
        case 3:
            result = "ACK";
            break;
        case 4:
            result = "FIN";
            break;
        default:
            result ="UNDEFINED";
            break;
    }
    return result;
}

void Console::ConnectionEstablished() {
    std::cout<<"Connection is established."<<std::endl;
}