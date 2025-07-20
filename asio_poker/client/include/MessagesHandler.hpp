#pragma once
#include <string>
#include "../../server/include/Constants.hpp"
//enum MessageType {
//    POCKET_CARDS = 1,
//    FLOP,
//    ANOTHER_CARD,
//    RAISE,
//    CALL,
//    PASS = 6,
//    ERROR = 7
//};

class MessagesHandler {
    public:
        MessagesHandler();
        //MessageType GetMessageType(const std::string&) const;
        std::array<struct Card, pocket_cards> ResolvePocketCardsMessage(const std::string&) const;
        std::array<struct Card, flop_size> ResolveFlopMessage(const std::string&) const;
        struct Card ResolveAnotherCardMessage(const std::string&) const;
};

