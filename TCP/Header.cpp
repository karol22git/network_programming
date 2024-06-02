
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
Header::Header( _16bits source, _16bits destination ) {

    source_port = source;
    destination_port = destination;

    sequence_number = 0;
    acknowledgment_number = 0;
    data = 0;
    options = 0;
    checksum = 0;
    urgent_pointer = 0;
    window = 0;
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