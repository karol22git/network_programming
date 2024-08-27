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
}

void Host::FetchDataFromNetwork() {
    struct Datagram fetchedDatagram;
    for(;;) {
        fetchedDatagram = endpoint->Fetch(ip);
        if(fetchedDatagram.segment.header != nullptr) {
            datagrams.push(fetchedDatagram);
        }
        CheckForReceivedData();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Host::CheckForReceivedData() {
    if(datagrams.size() != 0) {
        ProceedDatagram(datagrams.front());
        datagrams.pop();
    }
}

void Host::ProceedDatagram(struct Datagram datagram) {
    HeaderType hType = datagram.segment.header->GetHeaderType();
    console->Log(this,datagram);
    if(isConnectionEstablished) {
        if(hType == HeaderType::ACK) {
            _32bits ackNumber = datagram.segment.header->GetAcknowledgmentNumber();
            AcknowledgeSegment(ackNumber);
        }
        else {
            PrepareAcknowledgment(datagram.source_ip, datagram.segment.header->GetSourcePort(),datagram.segment.header->GetSequenceNumber());
        }
    }
    else {
        if(hType == HeaderType::SYN && state == States::LISTEN) {
            InitializeSequenceNumbers(datagram.segment.header->GetSequenceNumber());
            ThreeWayHandshakeStageOne(datagram.source_ip, datagram.segment.header->GetSourcePort());
            SetState(States::SYN_RECEIVED);
        }
        else if(hType == HeaderType::ACK && state == States::SYN_RECEIVED) {
            ThreeWayHandshakeStageThree();
        }
        else if(hType == HeaderType::SYNACK && state == States::SYN_SENT) {
           InitializeIRS(datagram.segment.header->GetSequenceNumber());
           ThreeWayHandshakeStageTwo(datagram.source_ip, datagram.segment.header->GetSourcePort());
        }
        else {
            std::cout<<"Error has occured!"<<std::endl;
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
    receiver = std::thread(&Host::FetchDataFromNetwork,this);
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
}

void Host::PostDataOnNetwork() {
    for(;;) {
        if(data_to_be_send.size() != 0) {
            data_to_be_send.front().segment.header->SetSequenceNumber(tcb.snd_nxt);
            MarkAsSend(data_to_be_send.front());
            UpdateSndNxt();
            endpoint->Post(data_to_be_send.front());
            data_to_be_send.pop();
        }
        if(acknowledgments_for_data.size() != 0) {
            endpoint->Post(acknowledgments_for_data.front());
            acknowledgments_for_data.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

void Host::ThreeWayHandshakeStageTwo(std::string source_ip, _16bits source_port) {
    struct Datagram newDatagram = PrepareDatagram(ip,source_ip);
    newDatagram.segment.header = generator->GenerateAckHeader(port, source_port, tcb.snd_nxt);
    endpoint->Post(newDatagram);
    UpdateSndNxt();
    ConnectinonHasBeenEstablished();
    OpenConnection();
}
void Host::ThreeWayHandshakeStageThree() {
    sender = std::thread(&Host::PostDataOnNetwork,this);
    ConnectinonHasBeenEstablished();

}

void Host::ConnectinonHasBeenEstablished() {
    isConnectionEstablished = true;
    console->ConnectionEstablished();
    SetState(States::ESTABLISHED);
    retransmiter = std::thread(&Host::CheckForRetransmission,this);
}

void Host::PrepareAcknowledgment(std::string destination_ip, _16bits destination_port, _32bits acknowledgment_number) {
    struct Datagram ackDatagram;
    struct Segment ackSegment;
    ackDatagram.segment = ackSegment;
    ackDatagram.source_ip = ip;
    ackDatagram.ip = destination_ip;
    ackDatagram.segment.data = 0;
    ackDatagram.segment.header = generator->GenerateAckHeader(port, destination_port, acknowledgment_number);
    acknowledgments_for_data.push(ackDatagram);

}

void Host::Wait() {
    receiver.join();
    sender.join();
    retransmiter.join();
}

void Host::MarkAsSend(struct Datagram datagram) {
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
    auto p = std::make_pair(datagram, t);
    data_to_be_acknowledgment.push_back(p);
}

void Host::CheckForRetransmission() {
    std::chrono::steady_clock::time_point now, datagramSendTime;
    for(;;) {
    now = std::chrono::steady_clock::now();
    for(auto it = data_to_be_acknowledgment.begin() ; it != data_to_be_acknowledgment.end() ; ++it) {
        datagramSendTime = std::get<1>(*it);
        auto time_since_send =  std::chrono::duration_cast<std::chrono::milliseconds>(now - datagramSendTime).count();
        std::cout<<time_since_send<<std::endl;
        if(time_since_send > RETRANSMISSION_TIME_OUT) {
            auto newPair = std::make_pair(std::get<0>(*it), now);
            data_to_be_acknowledgment.erase(it);
            endpoint->Post(std::get<0>(newPair));
            data_to_be_acknowledgment.push_back(newPair);
            std::cout<<"I send again segment: "<<std::get<0>(*it).segment.header->GetSequenceNumber()<<std::endl; 
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Host::AcknowledgeSegment(_32bits ackNumber) {
    for(auto it = data_to_be_acknowledgment.begin() ; it != data_to_be_acknowledgment.end() ; ++it) {
        auto datagram_waiting_for_be_acknowledged = std::get<0>(*it);
        if(datagram_waiting_for_be_acknowledged.segment.header->GetSequenceNumber() == ackNumber) {
            data_to_be_acknowledgment.erase(it);
                std::cout<<"I acknowledged segmment: "<<ackNumber<<std::endl;
                break;
        }
    }
}