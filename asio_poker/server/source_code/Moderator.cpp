#include "../include/Moderator.hpp"

Moderator::Moderator(): croupier(std::make_unique<Croupier>()), currentStage(Stage::PRE_FLOP) {
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

int Moderator::WhoCalledRaise() const {
    return gm.whoCalledRaise;
}

void Moderator::CallRaise(int _id) {
    gm.whoCalledRaise = _id;
}

int Moderator::GetFirstAliveIndex() const {
    int returnIndex = 0;
    while(!players[returnIndex]->isAlive()) ++returnIndex;
    return returnIndex;
}

bool Moderator::TurnEndCondition() const {
    if(gm.didRaiseOccured) {
        return CurrentTurn() == gm.whoCalledRaise;
    }
    else {
        return CurrentTurn() == gm.startIndex;
    }
}

void Moderator::SetUpNextStage() {
    if(currentStage == Stage::RIVER) {
        EndGame();
    }
    else {
        gm.didRaiseOccured = false;
        gm.whoCalledRaise = 0;
        gm.startIndex = GetFirstAliveIndex();
        //currentStage = currentStage +1;
        currentStage = static_cast<Stage>(static_cast<int>(currentStage) + 1);

    }
}

void Moderator::EndGame() {

}


Stage Moderator::FetchStage() const {
    return currentStage;
}

bool Moderator::CheckIfPlayerHaveEnouhgtMoney(const unsigned int _id) const {
    return players[_id]->GetMoneyLeft() > gm.stake;
}


void Moderator::Call(const unsigned int _id) {
    players[_id]->Call(gm.stake);
}

int Moderator::GetStake() const {
    return gm.stake;
}