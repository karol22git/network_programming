#pragma once
#include "Header.hpp"

struct Segment {
    std::shared_ptr<Header> header;
    int data;
    
};
