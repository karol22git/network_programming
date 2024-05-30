#pragma once
#include "DataTypes.hpp"

class Header {

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
