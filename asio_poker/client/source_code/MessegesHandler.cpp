#include "../include/MessagesHandler.hpp"
#include <map>

MessagesHandler::MessagesHandler() {}


//MessageType MessagesHandler::GetMessageType(const std::string& msg) const {
//    std::map<std::string, MessageType> tmpMap  = {
//        {"[POCKET_CARDS]", MessageType::POCKET_CARDS},
//        {"[FLOP]",MessageType::FLOP},
//        {"[ANOTHER_CARD]",MessageType::ANOTHER_CARD},
//        {"[RAISE]",MessageType::RAISE},
//        {"[CALL]",MessageType::CALL},
//        {"[PASS]",MessageType::PASS}};
//
//    for(const auto& [key,value]: tmpMap) {
//        if(std::find(msg.begin(),msg.end(),key) != msg.end()) return value;
//    }
//    return MessageType::ERROR;
//}