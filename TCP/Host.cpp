#include "Host.hpp"



Host::Host(std::string _ip, _16bits _port) {
    ip = _ip;
    port = _port;
}
void Host::SetState(States newState) {
    state = newState;
}

void Host::OpenForConnectionPassively() {
    SetState(States::LISTEN);
    receiver = std::thread(&Host::FetchDataFromNetwork,this);
}

void Host::FetchDataFromNetwork() {
    struct Datagram fetchedDatagram;// = endpoint.GetDatagram(ip);
    for(;;) {
        fetchedDatagram = endpoint->Fetch(ip);
        if(fetchedDatagram.segment.header != nullptr) {
            datagrams.push(fetchedDatagram);
        }
        CheckForReceivedData();
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
        
    }
    else {
        ProceedThreeWayHandshake(datagram);
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
    newDatagram.segment = newSegment;

    endpoint->Post(newDatagram);
    SetState(States::SYN_SENT);
}
