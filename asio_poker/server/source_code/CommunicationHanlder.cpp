#include "../include/CommunicationHandler.hpp"
#include "../include/Moderator.hpp"
#include "../include/UdpServer.hpp"
CommunicationHandler::CommunicationHandler(UdpServer* _parent) {parent = _parent;}

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

void CommunicationHandler::HandleNormalMessage(const std::string& msg)  {
    MessageType msgType = GetMessageType(msg);
    switch(msgType) {
        case MessageType::RAISE:

            break;
        case MessageType::CALL:
            Just();
            break;  
        case MessageType::PASS:
            moderator->Kill(ShellId(msg));
            parent->BroadcastMessage(GenerateKillMessage(ShellId(msg)));
            break;
        case MessageType::MSG_EXIT:
            moderator->Kill(ShellId(msg));
            break;
        default:
            break;
    }
}

void CommunicationHandler::SetModerator(Moderator* _moderator) {
    moderator = _moderator;
}

void CommunicationHandler::Just() {
    parent->BroadcastTurn();
}

int CommunicationHandler::ShellId(const std::string& msg) const {
    std::regex rgx("\\|(.*?)\\|");
    std::smatch match;
    while (std::regex_search(msg, match, rgx)) {
        return std::atoi(match[1]);
        std::cout << match[1] << std::endl;
    }
    return -1;
}

std::string CommunicationHandler::GenerateKillMessage(unsigned int _id) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::MSG_EXIT))
    .SetParams(std::to_string(_id))
    .Build();
    return msg;
}