#pragma once
#include "Header.hpp"
#include <memory>
class HeaderGenerator {
    public:
        std::shared_ptr<Header> GeneratePlainHeader(_16bits source, _16bits destination);
        std::shared_ptr<Header> GenerateSynHeader(_16bits, _16bits, _32bits);
        std::shared_ptr<Header> GenerateSynAckHeader(_16bits, _16bits, _32bits, _32bits);
    private:
        _32bits initial_sequence_number;
};