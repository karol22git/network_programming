#include "Host.hpp"
#include <iostream>


Host::Host(std::string _ip, _16bits _port) {
    ip = _ip;
    port = _port;
    clock = std::make_unique<Clock>();
    generator = std::make_unique<HeaderGenerator>();
    console = std::make_unique<Console>();
}
void Host::SetState(States newState) {
    state = newState;
}

void Host::OpenForConnectionPassively() {
    SetState(States::LISTEN);
    console->PrintState(this);
    receiver = std::thread(&Host::FetchDataFromNetwork,this);
    receiver.join();
}

void Host::FetchDataFromNetwork() {
    struct Datagram fetchedDatagram;
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
        console->Log(this, datagram);
    }
    else {
        console->Log(this,datagram);
        HeaderType hType = datagram.segment.header->GetHeaderType();
        if(hType == HeaderType::SYN && state == States::LISTEN) {
            InitializeSequenceNumbers(datagram.segment.header->GetSequenceNumber());
            //tcb.irs = datagram.segment.header->GetSequenceNumber();
           //tcb.iss = clock->GetSequenceNumber();
            //struct Datagram newDatagram = PrepareDatagram(ip, datagram.source_ip);
            //tcb.snd_nxt = tcb.irs + 1;
            //newDatagram.segment.header = generator->GenerateSynAckHeader(port, datagram.segment.header->GetSourcePort(), tcb.iss, tcb.snd_nxt);
            //tcb.snd_nxt = tcb.snd_nxt +1;
            //endpoint->Post(newDatagram);
            //console->Log(this,datagram);
            ThreeWayHandshakeStageOne(datagram.source_ip, datagram.segment.header->GetSourcePort());
            SetState(States::SYN_RECEIVED);
        }
        else if(hType == HeaderType::ACK && state == States::SYN_RECEIVED) {
            //isConnectionEstablished == true;
            //console->Log(this,datagram);
            //console->ConnectionEstablished();
            //SetState(States::ESTABLISHED);
            //OpenConnection();
            ThreeWayHandshakeStageThree();
        }
        else if(hType == HeaderType::SYNACK && state == States::SYN_SENT) {
           // tcb.irs = datagram.segment.header->GetSequenceNumber();
           InitializeIRS(datagram.segment.header->GetSequenceNumber());
            struct Datagram newDatagram = PrepareDatagram(ip,datagram.source_ip);
           // tcb.snd_nxt = tcb.irs +1;
            newDatagram.segment.header = generator->GenerateAckHeader(port, datagram.segment.header->GetSourcePort(), tcb.snd_nxt);
            tcb.snd_nxt = tcb.snd_nxt +1;
            endpoint->Post(newDatagram);
            isConnectionEstablished == true;
            //console->Log(this,datagram);
            console->ConnectionEstablished();
            SetState(States::ESTABLISHED);
           // std::this_thread::sleep_for(std::chrono::milliseconds(250));
            OpenConnection();
        }
        else {
            std::cout<<"Error has occured!"<<isConnectionEstablished<<std::endl;
        }
    }
}



void Host::OpenForConnectionActively(std::string destination_ip, _16bits destination_port) {
    tcb.iss = clock->GetSequenceNumber();


    struct Datagram newDatagram = PrepareDatagram(ip,destination_ip);
    newDatagram.segment.header = generator->GenerateSynHeader(port,destination_port,tcb.iss);

    endpoint->Post(newDatagram);
    std::cout<<"Current state: SYS_SENT"<<std::endl;
    SetState(States::SYN_SENT);
    //OpenForConnectionPassively();
    receiver = std::thread(&Host::FetchDataFromNetwork,this);
    receiver.join();
}

struct Datagram Host::PrepareDatagram(std::string source_ip, std::string destination_ip) {
    struct Datagram newDatagram;
    struct Segment newSegment;
    newSegment.data = 0;
    newDatagram.ip = destination_ip;    
    newDatagram.source_ip = source_ip;
    newDatagram.segment = newSegment;
    return newDatagram;

}

States Host::GetState() {
    return state;
}

void Host::PrepareDataToBeSend(int bytes, std::string destination_ip, _16bits destination_port) {
    int number_of_segments =static_cast<int>(bytes/(MAXIMUM_SEGMENT_SIZE - HEADER_SIZE)) + 1;
    int bytes_left = bytes;
    for(int i = 0 ; i < number_of_segments ; ++i) {
        struct Datagram newDatagram;
        newDatagram.source_ip = ip;
        newDatagram.ip = destination_ip;

        struct Segment newSegment;
        if(bytes_left > MAXIMUM_SEGMENT_SIZE - HEADER_SIZE) {
            newSegment.data = MAXIMUM_SEGMENT_SIZE - HEADER_SIZE;
        }
        else {
            newSegment.data = bytes_left;
        }
        newDatagram.segment = newSegment;
        newDatagram.segment.header = generator->GeneratePlainHeader(port, destination_port);
        bytes_left = bytes_left - (MAXIMUM_SEGMENT_SIZE - HEADER_SIZE);
        data_to_be_send.push(newDatagram);
    }
}

void Host::OpenConnection() {
    sender = std::thread(&Host::PostDataOnNetwork,this);
    sender.join();
}

void Host::PostDataOnNetwork() {
    for(;;) {
        if(data_to_be_send.size() != 0) {
            std::cout<<"tut"<<std::endl;
            data_to_be_send.front().segment.header->SetSequenceNumber(tcb.snd_nxt);
            tcb.snd_nxt = tcb.snd_nxt +1;
            endpoint->Post(data_to_be_send.front());
            data_to_be_send.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        std::cout<<data_to_be_send.size()<<std::endl;
    }
}

void Host::InitializeSequenceNumbers(_32bits received_sn) {
    tcb.irs = received_sn;
    tcb.iss = clock->GetSequenceNumber();
    tcb.snd_nxt = tcb.irs;
}

void Host::InitializeIRS(_32bits received_sn) {
    tcb.irs = received_sn;
    tcb.snd_nxt = tcb.irs;
}

void Host::UpdateSndNxt() {
    tcb.snd_nxt = tcb.snd_nxt +1;
}

void Host::ThreeWayHandshakeStageOne(std::string source_ip, _16bits source_port) {
    struct Datagram newDatagram = PrepareDatagram(ip, source_ip);
    newDatagram.segment.header = generator->GenerateSynAckHeader(port, source_port, tcb.iss, tcb.snd_nxt);
    endpoint->Post(newDatagram);
    UpdateSndNxt();
}

void Host::ThreeWayHandshakeStageTwo() {

}
void Host::ThreeWayHandshakeStageThree() {
    isConnectionEstablished == true;
            //console->Log(this,datagram);
    console->ConnectionEstablished();
    SetState(States::ESTABLISHED);
}