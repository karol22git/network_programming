#pragma once
#include <wx/wx.h>
#include <string>
#include "MessageBuilder.hpp"
#include "../../server/include/Constants.hpp"
class CommunicationHandler {
    public:
        CommunicationHandler();
        std::string GeneratePassMessage(const unsigned int) const;
        std::string GenerateRaiseMessage(const unsigned int, const unsigned int) const;
        std::string GenerateCallMessage(const unsigned int) const;
        std::string MessageTypeToString(MessageType type) const;
        void SendAnyAction(wxCommandEvent& event);
};