#include "../include/Moderator.hpp"

Moderator::Moderator(): croupier(std::make_unique<Croupier>()) {

}

void Moderator::StartGame() {
    for(const auto player: players) player->AcceptCards(croupier->GetPocketCards());
}

void Moderator::CreateNewPlayer(unsigned int id) {
    players.push_back(new Player(id));
}

