#include "../include/Mediator.hpp"

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
}

Mediator::Mediator() {}