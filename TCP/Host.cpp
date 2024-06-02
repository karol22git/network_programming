#include "Host.hpp"


void Host::SetState(States newState) {
    state = newState;
}

void Host::OpenForConnectionPassively() {
    SetState(States::LISTEN);
    for(;;) {
        receiver = std::thread(&Host::FetchDataFromNetwork,this);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        CheckForReceivedData();
    }
}

void Host::FetchDataFromNetwork() {
    struct Datagram fetchedDatagram = endpoint.GetDatagram(ip);
    if(fetchedDatagram != nullptr) {
        datagrams.pushback(fetchedDatagram);
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