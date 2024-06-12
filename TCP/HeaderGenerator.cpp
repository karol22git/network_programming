#include "HeaderGenerator.hpp"



std::shared_ptr<Header> HeaderGenerator::GeneratePlainHeader(_16bits source, _16bits destination) {
    return std::make_shared<Header>(source,destination);
}

std::shared_ptr<Header> HeaderGenerator::GenerateSynHeader(_16bits source_port, _16bits destination_port) {
    std::shared_ptr<Header> syn = std::make_shared<Header>(source_port,destination_port);
    syn->SetFlag(Flags::syn);
    return syn;
}

std::shared_ptr<Header> HeaderGenerator::GenerateSynAckHeader(_16bits source_port, _16bits destination_port) {
    std::shared_ptr<Header> synack = std::make_shared<Header>(source_port,destination_port);
    synack->SetFlag(Flags::ack);
    synack->SetFlag(Flags::syn)
    return synack;
}