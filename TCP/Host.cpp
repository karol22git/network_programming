#include "Host.hpp"


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
        fetchedDatagram = endpoint.Fetch(ip);
        if(fetchedDatagram != nullptr) {
            datagrams.pushback(fetchedDatagram);
        }
        CheckForReceivedData();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void Host::CheckForReceivedData() {
    if(datagrams.size() != 0) {
        ProceedDatagram(datagrams.pop());
    }
}

void Host::ProceedDatagram(struct Datagram datagarm) {
    if(isConnectionEstablished) {
        
    }
    else {
        ProceedThreeWayHandshake(datagram);
    }
}

void Host::ProceedThreeWayHandshake(struct Datagram datagram) {

}


void Host::OpenForConnectionActively(std::string ip, _16bits destination_port) {
    
}
