
#include "Header.hpp"

void Header::SetFlag(Flags flag) {
    switch(flag) {
        case 1: flags.cwr = 1;
            break;
        case 2: flags.ece = 1;
            break;
        case 3: flags.urg = 1;
            break; 
        case 4: flags.ack = 1;
            break;
        case 5: flags.psh = 1;
            break;
        case 6: flags.rst = 1;
            break;  
        case 7: flags.syn = 1;
            break;
        case 8: flags.fin = 1;
            break;
        default:
            break;
    }
}

Header::Header() {
    source_port = 0;
    destination_port = 0;
    sequence_number = 0;
    acknowledgment_number = 0;
    data = 0;
    options = 0;
    checksum = 0;
    urgent_pointer = 0;
    window_size = 0;
    flags.cwr = 0;
    flags.ece = 0;
    flags.urg = 0;
    flags.ack = 0;
    flags.psh = 0;
    flags.rst = 0;
    flags.syn = 0;
    flags.fin = 0;

    data_offset.a = 0;
    data_offset.b = 0;
    data_offset.c = 0;
    data_offset.d = 0;
    
    reserved.a = 0;
    reserved.b = 0;
    reserved.c = 0;
    reserved.d = 0;
}
Header::Header( _16bits source, _16bits destination ) {
    Header();
    source_port = source;
    destination_port = destination;

}

Header::Header(_32bits _sequence_number) {
    sequence_number = _sequence_number;
}


_32bits Header::GetSequenceNumber() {
    return sequence_number;
}

_32bits Header::GetAcknowledgmentNumber() {
    return acknowledgment_number;
}


_16bits Header::GetSourcePort() {
    return source_port;
}

_16bits Header::GetDestinationPort() {
    return destination_port;
}

_4bits Header::GetDataOffset() {
    return data_offset;
}

_4bits Header::GetReserved() {
    return reserved;
}

_8bits Header::GetFlags() {
    return flags;
}

_16bits Header::GetWindowSize() {
    return window_size;
}

_16bits Header::GetChecksum() {
    return checksum;
}

_16bits Header::GetUrgentPointer() {
    return urgent_pointer;
}

_32bits Header::GetOptions() {
    return options;
}

void Header::SetSourcePort(_16bits sourcePort) {
    source_port = sourcePort;
}

void Header::SetDestinationPort(_16bits destinationPort) {
    destination_port = destinationPort;
}

void Header::SetSequenceNumber(_32bits sequenceNumber) {
    sequence_number = sequenceNumber;
}

void Header::SetAcknowledgmentNumber(_32bits acknowlegmentNumber) {
    acknowledgment_number = acknowlegmentNumber;
}

void Header::SetDataOffset(_4bits dataOffset) {
    data_offset.a = dataOffset.a;
    data_offset.b = dataOffset.b;
    data_offset.c = dataOffset.c;
    data_offset.d = dataOffset.d;
}

void Header::SetReserved(_4bits res) {
    reserved.a = res.a;
    reserved.b = res.b;
    reserved.c = res.c;
    reserved.d = res.d;

}

void Header::SetFlags(_8bits flag) {
    flags.cwr = flag.cwr;
    flags.ece = flag.ece;
    flags.urg = flag.urg;
    flags.ack = flag.ack;
    flags.psh = flag.psh;
    flags.rst = flag.rst;
    flags.syn = flag.syn;
    flags.fin = flag.fin;
}

void Header::SetWindowSize(_16bits windowSize) {
    window_size = windowSize;
}

void Header::SetChecksum(_16bits cSum) {
    checksum = cSum;
}

void Header::SetUrgentPointer(_16bits urgentPointer) {
    urgent_pointer = urgentPointer;
}

void Header::SetOptions(_32bits op) {
    options = op;
}

HeaderType Header::GetHeaderType() {
    HeaderType result = HeaderTypes::UNDEFINED;
    if(flags.syn == 1 && flags.ack) {
        result = HeaderTypes::SYNACK;
    }
    else if(flags.syn == 1) {
        result = HeaderTypes::SYN;
    }
    return result;
}