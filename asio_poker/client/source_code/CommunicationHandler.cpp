#include "../include/CommunicationHandler.hpp"


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
            return "[CALL]";
        case 6:
            return "[PASS]";
        case 7:
            return "TURN";
        case 8:
            return "MSG_EXIT";
        case 9:
            return "[FORCED]";
        case 10:
            return "[SMALL_BLIND]";
        case 11:
            return "[BIG_BLIND]";
        case 12:
            return "[ACCEPT_CALL]";
        case 13:
            return "[POT]";
        default:
            return "ERROR";
    }
}


CommunicationHandler::CommunicationHandler() {

}

void CommunicationHandler::SendAnyAction(wxCommandEvent& event) {}


std::string CommunicationHandler::GeneratePassMessage(const unsigned int _id) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::PASS))
    .SetId(_id)
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateRaiseMessage(const unsigned int _id, const unsigned int stake) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::RAISE))
    .SetId(_id)
    .SetParams(std::to_string(stake))
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateCallMessage(const unsigned int _id) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::CALL))
    .SetId(_id)
    .Build();
    return msg;
}




std::string CommunicationHandler::GenerateSmallBlindMessage(const unsigned int _id) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::SMALL_BLIND))
    .SetId(_id)
    .Build();
    return msg;
}
std::string CommunicationHandler::GenerateBigBlindMessage(const unsigned int _id) const {
 MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::BIG_BIND))
    .SetId(_id)
    .Build();
    return msg;
}