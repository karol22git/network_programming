#pragma once
#include "Header.hpp"
#include <memory>
struct Segment {
    std::shared_ptr<Header> header;
    int data;
    
};
