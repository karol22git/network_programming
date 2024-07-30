#include "Host.hpp"
#include <iostream>


Host::Host(std::string _ip, _16bits _port) {
    ip = _ip;
    port = _port;
    clock = std::make_unique<Clock>();
    generator = std::make_unique<HeaderGenerator>();
    PrepareToConnection();
}
void Host::SetState(States newState) {
    state = newState;
}

void Host::OpenForConnectionPassively() {
    SetState(States::LISTEN);
    receiver = std::thread(&Host::FetchDataFromNetwork,this);
    receiver.join();
}

void Host::FetchDataFromNetwork() {
    struct Datagram fetchedDatagram;// = endpoint.GetDatagram(ip);
    for(;;) {
        fetchedDatagram = endpoint->Fetch(ip);
        if(fetchedDatagram.segment.header != nullptr) {
            datagrams.push(fetchedDatagram);
        }
        CheckForReceivedData();
        std::cout<<"looking for datagram to fetch..."<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void Host::CheckForReceivedData() {
    if(datagrams.size() != 0) {
        ProceedDatagram(datagrams.front());
        datagrams.pop();
    }
}

void Host::ProceedDatagram(struct Datagram datagram) {
    if(isConnectionEstablished) {
        std::cout<<"Hello World!"<<std::endl;
    }
    else {
        HeaderType hType = datagram.segment.header->GetHeaderType();
        if(hType == HeaderType::SYN && state == States::LISTEN) {
            tcb.irs = datagram.segment.header->GetSequenceNumber();
            tcb.iss = clock->GetSequenceNumber();
            struct Datagram newDatagram;
            struct Segment newSegment;
            newSegment.data = 0;
            newSegment.header = generator->GenerateSynAckHeader(port, datagram.segment.header->GetSourcePort(), tcb.iss, tcb.irs + 1);
            newDatagram.ip = datagram.source_ip;
            newDatagram.source_ip = ip;
            newDatagram.segment = newSegment;
            endpoint->Post(newDatagram);
            SetState(States::SYN_RECEIVED);
        }
        else if(hType == HeaderType::ACK && state == States::SYN_RECEIVED) {
            isConnectionEstablished == true;
            std::cout<<"Connection establishe!"<<std::endl;
        }
        else if(hType == HeaderType::SYNACK && state == States::SYN_SENT) {
            isConnectionEstablished == true;
            struct Datagram newDatagram;
            struct Segment newSegment;
            newSegment.data = 0;
            newSegment.header = generator->GenerateAckHeader(port, datagram.segment.header->GetSourcePort(), tcb.irs + 1);
            newDatagram.ip = datagram.source_ip;
            newDatagram.source_ip = ip;
            newDatagram.segment = newSegment;
            endpoint->Post(newDatagram);
            std::cout<<"Connection establishe!"<<std::endl;
        }
        else {
            if(hType == HeaderType::SYNACK) {
                std::cout<<"tut"<<std::endl;
            }
            else if(hType == HeaderType::UNDEFINED) {
                std::cout<<"tut2"<<std::endl;
            }
            else if(hType == HeaderType::SYN) {
                _8bits f = datagram.segment.header->GetFlags();
                std::cout<<"tut3"<<f.cwr<< f.ece << f.urg << f.ack << f.psh<<f.rst<<f.syn<<f.fin<< std::endl;
            } 
            std::cout<<"Error has occured!"<<std::endl;
        }
    }
}

void Host::ProceedThreeWayHandshake(struct Datagram datagram) {

}


void Host::OpenForConnectionActively(std::string destination_ip, _16bits destination_port) {
    //initial_sequance_number = clock->GetSequenceNumber();
    tcb.iss = clock->GetSequenceNumber();
    struct Datagram newDatagram;
    struct Segment newSegment;

    newSegment.header = generator->GenerateSynHeader(port,destination_port,tcb.iss);
    newSegment.data = 0;

    newDatagram.ip = destination_ip;
    newDatagram.source_ip = ip;
    newDatagram.segment = newSegment;

    endpoint->Post(newDatagram);
    SetState(States::SYN_SENT);
    //OpenForConnectionPassively();
    receiver = std::thread(&Host::FetchDataFromNetwork,this);
    receiver.join();
}


void Host::PrepareToConnection() {
    cStages.syn = false;
    cStages.synack = false;
    cStages.ack = false;
}