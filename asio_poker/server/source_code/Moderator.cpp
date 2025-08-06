#include "../include/Moderator.hpp"

Moderator::Moderator(): croupier(std::make_unique<Croupier>()) {
}

void Moderator::StartGame() {
    for(const auto player: players) player->AcceptCards(croupier->GetPocketCards());
    FetchFlop();
    turnManager = new TurnManager(players);
}

void Moderator::CreateNewPlayer(unsigned int id) {
    players.push_back(new Player(id));
}

std::vector<Player*> Moderator::GetPlayers() const {
    return players;
}

void Moderator::FetchFlop() {
    flopCards = croupier->GetFlop();
}

std::array<struct Card, flop_size> Moderator::GetFlop() const {
    return flopCards;
}

int Moderator::WhosTurn() const{
    return turnManager->GetNextTurn();
}

int Moderator::CurrentTurn() const {
    return turnManager->CurrentTurn();
}

bool Moderator::isWonBySurrender() const {
    unsigned int counter = 0;
    for(auto const p: players) {
        if(p->isAlive()) ++counter;
    }
    if(counter == 1) return true;
    else return false;
}

int Moderator::GetLastAlivePlayerId() const {
    for(const auto player: players) {
        if(player->isAlive()) return player->GetId();
    }
    return 0;
}

void Moderator::Kill(unsigned int _id) {
    players[_id]->Kill();
}