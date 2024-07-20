#include "HeaderGenerator.hpp"



std::shared_ptr<Header> HeaderGenerator::GeneratePlainHeader(_16bits source, _16bits destination) {
    return std::make_shared<Header>(source,destination);
}

std::shared_ptr<Header> HeaderGenerator::GenerateSynHeader(_16bits source_port, _16bits destination_port, _32bits init_sequance_number) {
    std::shared_ptr<Header> syn = std::make_shared<Header>(source_port,destination_port);
    syn->SetFlag(Flags::syn);
    syn->SetSequenceNumber(init_sequance_number);
    return syn;
}

std::shared_ptr<Header> HeaderGenerator::GenerateSynAckHeader(_16bits source_port, _16bits destination_port, _32bits init_sequance_number, _32bits acknowledgment_number) {
    std::shared_ptr<Header> synack = std::make_shared<Header>(source_port,destination_port);
    synack->SetFlag(Flags::ack);
    synack->SetFlag(Flags::syn);
    synack->SetSequenceNumber(init_sequance_number);
    synack->SetAcknowledgmentNumber(acknowledgment_number);
    return synack;
}