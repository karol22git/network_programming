#pragma once
#include "Segment.hpp"
#include <string>

struct Datagram {
    std::string ip;
    std::string source_ip;
    Segment segment;
};