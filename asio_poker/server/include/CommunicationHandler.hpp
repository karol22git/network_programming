#pragma once
#include <string>
#include "Constants.hpp"
#include "MessageBuilder.hpp"
class CommunicationHandler {
    public:
        CommunicationHandler();
        std::string MessageTypeToString(MessageType type) const;
        std::string GeneratePocketCardsMessage(const struct Card& c1, const struct Card& c2) const;
        std::string GenerateFlopMessage(const struct Card& c1, const struct Card& c2, const struct Card& c3) const;
        std::string GenerateAnotherCardMessage(const struct Card& c) const;
};

