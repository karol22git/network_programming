#pragma once
#include "DataTypes.hpp"
#include "Flags.hpp"

class Header {
    public:
        Header(_16bits source, _16bits destination);
        Header(_32bits);
        Header();
        _32bits GetSequenceNumber();
        _32bits GetAcknowledgmentNumber();
        _16bits GetSourcePort();
        _16bits GetDestinationPort();
        _4bits GetDataOffset();
        _4bits GetReserved();
        _8bits GetFlags();
        _16bits GetWindowSize();
        _16bits GetChecksum();
        _16bits GetUrgentPointer();
        _32bits GetOptions();
        void SetFlag(Flags);
        void SetSourcePort(_16bits);
        void SetDestinationPort(_16bits);
        void SetSequenceNumber(_32bits);
        void SetAcknowledgmentNumber(_32bits);
        void SetDataOffset(_4bits);
        void SetReserved(_4bits);
        void SetFlags(_8bits);
        void SetWindowSize(_16bits);
        void SetChecksum(_16bits);
        void SetUrgentPointer(_16bits);
        void SetOptions(_32bits);
    private:
        _32bits sequence_number;
        _32bits acknowledgment_number;
        _32bits data;
        _32bits options;

        _16bits source_port;
        _16bits destination_port;
        _16bits checksum;
        _16bits urgent_pointer;
        _16bits window_size;
        
        _8bits flags;

        _4bits data_offset;
        _4bits reserved;
};
