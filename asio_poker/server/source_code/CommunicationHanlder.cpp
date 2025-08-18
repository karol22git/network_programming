#include "../include/CommunicationHandler.hpp"
#include "../include/Moderator.hpp"
#include "../include/UdpServer.hpp"
CommunicationHandler::CommunicationHandler(UdpServer* _parent) {parent = _parent;}

std::string CommunicationHandler::MessageTypeToString(MessageType type)  {
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
        case 8 :
            return "EXIT";
        case 9:
            return "FORCED";
        case 10:
            return "SMALL_BLIND";
        case 11:
            return "BIG_BLIND";
        case 12:
            return "ACCEPT_CALL";
        case 13:
            return "STAKE";
        case 14:
            return "POT";
        case 15:
            return "SHOW_CARDS";
        case 16:
            return "SOLO_WIN";
        case 17:
            return "MULTI_WIN";
        case 18: 
            return "ACCEPT_RAISE";
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
    int messageAutorId = ShellId(msg);
    bool myCondition;
    int id;
    std::vector<std::string> parameters;
    if(msgType != MessageType::FORCED && messageAutorId != moderator->CurrentTurn()) return;
    switch(msgType) {
        case MessageType::RAISE:
            id = ShellId(msg);
            parameters = GetAllParameters(msg);
            parent->logger->SimpleLog("tutaj");
            if(moderator->CheckIfRaiseIsPossible(id,std::stoi(parameters[0]))) {
                parent->logger->SimpleLog("tutaj2");
                moderator->Raise(id,std::stoi(parameters[0]));
                parent->SendMessage(GenerateAcceptRaiseMessage(moderator->GetNewWalletForPlayer(ShellId(msg))));
                parent->BroadcastMessage(GenerateStakeMessage(ShellId(msg),moderator->GetStake()));
                parent->BroadcastMessage(GeneratePotMessage(moderator->GetPot()));
                Just();
            }
            break;
        case MessageType::CALL:
            if(CheckIfCallEvenPossible(ShellId(msg))) {
                moderator->Call(ShellId(msg));
                moderator->UpdatePot(moderator->GetStake());
                //parent->logger->SimpleLog("Moge zrobic call");
                parent->SendMessage(GenerateAcceptCallMessage(moderator->GetNewWalletForPlayer(ShellId(msg))));
                parent->BroadcastMessage(GenerateStakeMessage(ShellId(msg),moderator->GetStake()));
                parent->BroadcastMessage(GeneratePotMessage(moderator->GetPot()));
                Just();
            }
            else {
                moderator->Kill(ShellId(msg));
                parent->BroadcastMessage(GenerateKillMessage(ShellId(msg)));
            }
            myCondition = moderator->TurnEndCondition();
            if(myCondition) moderator->SetUpNextStage();
            break;  
        case MessageType::PASS:
            moderator->Kill(ShellId(msg));
            parent->BroadcastMessage(GenerateKillMessage(ShellId(msg)));
            break;
        case MessageType::MSG_EXIT:
            moderator->Kill(ShellId(msg));
            moderator->CheckForShutdown();
            break;
        case MessageType::FORCED:
            if(messageAutorId == moderator->CurrentTurn())moderator->WhosTurn();
            moderator->Kill(ShellId(msg));
            parent->BroadcastMessage(GenerateKillMessage(ShellId(msg)));
            moderator->CheckForShutdown();
            break;
        case MessageType::SMALL_BLIND:
            moderator->SmallBlind(ShellId(msg));
            moderator->UpdatePot(moderator->GetStake());
            parent->BroadcastMessage(GenerateStakeMessage(ShellId(msg),small_blind));
            parent->SendMessage(GenerateAcceptCallMessage(moderator->GetNewWalletForPlayer(ShellId(msg))));
                //parent->BroadcastMessage(GenerateStakeMessage(ShellId(msg),moderator->GetStake()));
            parent->BroadcastMessage(GeneratePotMessage(moderator->GetPot()));
            Just();
            break;
        case MessageType::BIG_BLIND:
            moderator->BigBlind(ShellId(msg));
            moderator->UpdatePot(moderator->GetStake());
            parent->BroadcastMessage(GenerateStakeMessage(ShellId(msg),small_blind));
            parent->SendMessage(GenerateAcceptCallMessage(moderator->GetNewWalletForPlayer(ShellId(msg))));
                //parent->BroadcastMessage(GenerateStakeMessage(ShellId(msg),moderator->GetStake()));
            parent->BroadcastMessage(GeneratePotMessage(moderator->GetPot()));
            Just();
            break;
        default:
            break;
    }
}

bool CommunicationHandler::CheckIfCallEvenPossible(const unsigned int _id) const {
    return moderator->CheckIfPlayerHaveEnouhgtMoney(_id);
}

void CommunicationHandler::SetModerator(Moderator* _moderator) {
    moderator = _moderator;
}

void CommunicationHandler::Just() {
    parent->BroadcastTurn();
    parent->BroadcastMessage(GenerateStakeMessage(moderator->CurrentTurn(),moderator->GetStake()));
    if(moderator->FetchStage() == Stage::PRE_FLOP_STAGE && !moderator->didBigBlindOccured() && !moderator->didRaiseOccured()) {
        if(moderator->CurrentTurn() == moderator->GetLastPlayerId()) {
            parent->SendMessage(GenerateBigBindMessage(),moderator->CurrentTurn());
        }
    }
}

int CommunicationHandler::ShellId(const std::string& msg) const {
    std::regex rgx("\\|(.*?)\\|");
    std::smatch match;
    while (std::regex_search(msg, match, rgx)) {
        return std::stoi(match[1]);
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

std::string CommunicationHandler::GenerateSmallBindMessage() {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::SMALL_BLIND))
    .SetParams(std::to_string(0))
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateBigBindMessage() {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::BIG_BLIND))
    .SetParams(std::to_string(quorum -1))
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateAcceptCallMessage(int money) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::ACCEPT_CALL))
    .SetParams(std::to_string(money))
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateStakeMessage(int id, int stake) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::STAKE))
    .SetParams(std::to_string(id))
    .SetParams(std::to_string(stake))
    .Build();
    return msg;
}


std::string CommunicationHandler::GeneratePotMessage(int pot) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::POT))
    .SetParams(std::to_string(pot))
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateShowCardsMessage(int _id, struct Card& c1, struct Card& c2) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::SHOW_CARDS))
    .SetParams(std::to_string(_id))
    .SetParams(c1.toString())
    .SetParams(c2.toString())
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateSoloWinMessage(int _id) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::SOLO_WIN))
    .SetParams(std::to_string(_id))
    .Build();
    return msg;
}

std::string CommunicationHandler::GenerateMultiWinMessage(std::vector<int> winners) const {
    MessageBuilder mb;
    mb = mb.SetHeader(MessageTypeToString(MessageType::MULTI_WIN));
    for(auto id: winners) mb = mb.SetParams(std::to_string(id));
    return mb.Build();
}

std::vector<std::string> CommunicationHandler::GetAllParameters(const std::string& msg) const {
    std::vector<std::string> result;
    std::regex pattern("\\{([^}]*)\\}");
    std::smatch match;
    std::string::const_iterator start = msg.begin();
    std::string::const_iterator end = msg.end();
    unsigned int index = 0;
    while (std::regex_search(start, end, match, pattern)) {
        //std::cout << "Znaleziono: " << match[1] << std::endl;
        result.push_back(match[1]);
        start = match[0].second;
    }
    return result;
}

std::string CommunicationHandler::GenerateAcceptRaiseMessage(int money) const {
    MessageBuilder mb;
    auto msg = mb.SetHeader(MessageTypeToString(MessageType::ACCEPT_RAISE))
    .SetParams(std::to_string(money))
    .Build();
    return msg;
}