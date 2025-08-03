#pragma once
#include <wx/wx.h>
#include <string>
#include "MessageBuilder.hpp"
class CommunicationHandler {
    public:
        CommunicationHandler();
        void SendAnyAction(wxCommandEvent& event);
};