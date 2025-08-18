#pragma once
#include <string>
#include "Constants.hpp"
#include "MessageBuilder.hpp"
#include <regex>

class Moderator;
class UdpServer;
class CommunicationHandler {
    public:
        CommunicationHandler(UdpServer*);
        static std::string MessageTypeToString(MessageType type) ;
        std::string GeneratePocketCardsMessage(const struct Card& c1, const struct Card& c2) const;
        std::string GenerateFlopMessage(const struct Card& c1, const struct Card& c2, const struct Card& c3) const;
        std::string GenerateAnotherCardMessage(const struct Card& c) const;
        std::string GenerateTurnMessage(unsigned int _id) const;
        std::string GenerateKillMessage(unsigned int _id) const;
        std::string GenerateAcceptCallMessage(int money) const;
        std::string GenerateAcceptRaiseMessage(int money) const;
        std::string GenerateStakeMessage(int, int) const;
        std::string GeneratePotMessage(int) const;
        std::string GenerateShowCardsMessage(int, struct Card& c1, struct Card& c2) const;
        std::string GenerateSoloWinMessage(int) const;
        std::string GenerateMultiWinMessage(std::vector<int>) const;
        std::vector<std::string> GetAllParameters(const std::string& msg) const;
        static std::string GenerateSmallBindMessage();
        static std::string GenerateBigBindMessage();
        void HandleNormalMessage(const std::string&);
        void SetModerator(Moderator*);
        void Just();
        int ShellId(const std::string&) const;
        bool CheckIfCallEvenPossible(const unsigned int) const;
        private:
            Moderator* moderator;
            UdpServer* parent;
};      

