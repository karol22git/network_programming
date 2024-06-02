#pragma once
#include "Header.hpp"

class HeaderGenerator {
    public:
        std::shared_ptr<Header> GeneratePlainHeader(_16bits source, _16bits destination);
        std::shared_ptr<Header> GenerateSynHeader(_16bits, _16bits);
    private:
        _32bits initial_sequence_number;
};