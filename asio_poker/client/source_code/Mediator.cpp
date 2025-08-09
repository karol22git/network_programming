#include "../include/Mediator.hpp"
#include "../include/Player.hpp"
Mediator* Mediator::instance = nullptr;
void Mediator::Init() {
    instance = new Mediator();
}
Mediator& Mediator::GetInstance() {
    return *instance;
}

void Mediator::SetClient(std::shared_ptr<UdpClient> _client) {
    client = _client;
}

void Mediator::SetActionPanel(ActionPanel* _actionPanel) {
    actionPanel = _actionPanel;
    Bind();
}

Mediator::Mediator(): communicationHandler(new CommunicationHandler()) {}

void Mediator::Bind() {
    auto passButton = actionPanel->GetPassButton();
    auto raiseButton = actionPanel->GetRaiseButton();
    auto callButton = actionPanel->GetCallButton();
    auto bigBlindButton = actionPanel->GetBigBlindButton();
    auto smallBlindButton= actionPanel->GetSmallBlindButton();
    passButton->Bind(wxEVT_BUTTON, &Mediator::Pass,this);
    raiseButton->Bind(wxEVT_BUTTON, &Mediator::Raise, this);
    callButton->Bind(wxEVT_BUTTON, &Mediator::Call, this);
    smallBlindButton->Bind(wxEVT_BUTTON,&Mediator::SmallBlind, this);
    bigBlindButton->Bind(wxEVT_BUTTON,&Mediator::BigBlind,this);
}

void Mediator::Pass(wxCommandEvent& event) {
    auto msg = communicationHandler->GeneratePassMessage(Player::GetInstance().GetId());
    client->SendMessage(msg);
}

void Mediator::Raise(wxCommandEvent& event) {
    auto msg = communicationHandler->GenerateRaiseMessage(Player::GetInstance().GetId(),100);
    client->SendMessage(msg);
}

void Mediator::Call(wxCommandEvent& event) {
    auto msg = communicationHandler->GenerateCallMessage(Player::GetInstance().GetId());
    client->SendMessage(msg);
}

void Mediator::SmallBlind(wxCommandEvent& event) {
    auto msg = communicationHandler->GenerateSmallBlindMessage(Player::GetInstance().GetId());
    client->SendMessage(msg);
    actionPanel->Rearrange();
}

void Mediator::BigBlind(wxCommandEvent& event) {
    auto msg = communicationHandler->GenerateBigBlindMessage(Player::GetInstance().GetId());
    client->SendMessage(msg);
    actionPanel->Rearrange();
}