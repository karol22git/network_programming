#pragma once
#include <string>
#include "HeaderTypes.hpp"
class Host;
class Console {
    public:
        Console();
        void PrintState(Host*);
        void PrintSegmentInfo(struct Datagram);
        void Log(Host*, struct Datagram);
        void ConnectionEstablished();
    private:
        std::string HeaderTypeToString(HeaderType);
};