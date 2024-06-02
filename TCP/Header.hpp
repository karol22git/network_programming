#pragma once
#include "DataTypes.hpp"
#include "Flags.hpp"
class Header {
    public:
        Header(_16bits source, _16bits destination);
        _32bits GetSequenceNumber();
        _32bits GetAcknowledgmentNumber();
        _16bits GetSourcePort();
        _16bits GetDestinationPort();
        void SetFlag(Flags)
    private:
        _32bits sequence_number;
        _32bits acknowledgment_number;
        _32bits data;
        _32bits options;

        _16bits source_port;
        _16bits destination_port;
        _16bits checksum;
        _16bits urgent_pointer;
        _16bits window;
        
        _8bits flags;

        _4bits data_offset;
        _4bits reserved;
};
