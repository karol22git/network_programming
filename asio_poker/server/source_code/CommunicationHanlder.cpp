#include "../include/CommunicationHandler.hpp"

CommunicationHandler::CommunicationHandler() {}

std::string CommunicationHandler::MessageTypeToString(MessageType type) const {
    switch(type) {
        case 1:
            return "POCKET_CARDS";
        case 2:
            return "FLOP";
        case 3:
            return "ANOTHER_CARD";
        case 4: 
            return "RAISE";
        case 5:
            return "CALL";
        case 6:
            return "PASS";
        case 7:
            return "TURN";
        default:
            return "ERROR";
    }
}

std::string CommunicationHandler::GeneratePocketCardsMessage(const struct Card& c1, const struct Card& c2) const {
    MessageBuilder mb;
    std::string msg = mb.SetHeader(MessageTypeToString(MessageType::POCKET_CARDS)).SetParams(c1.toString()).SetParams(c2.toString()).Build();
    return msg;
}

std::string CommunicationHandler::GenerateFlopMessage(const struct Card& c1, const struct Card& c2, const struct Card& c3) const {
    MessageBuilder mb;
    std::string msg  = mb.SetHeader(MessageTypeToString(MessageType::FLOP))
    .SetParams(c1.toString())
    .SetParams(c2.toString())
    .SetParams(c3.toString())
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateAnotherCardMessage(const struct Card& c) const {
    MessageBuilder mb;
    std::string msg = mb.SetHeader(MessageTypeToString(MessageType::ANOTHER_CARD))
    .SetParams(c.toString())
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateTurnMessage(unsigned int _id) const {
    MessageBuilder mb;
    std::string msg = mb.SetHeader(MessageTypeToString(MessageType::TURN))
    .SetParams(std::to_string(_id))
    .Build();
    return msg;
}