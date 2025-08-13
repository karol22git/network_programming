#include "../include/Moderator.hpp"
#include "../include/UdpServer.hpp"
Moderator::Moderator(UdpServer* _parent): croupier(std::make_unique<Croupier>()), currentStage(Stage::PRE_FLOP_STAGE), parent(_parent) {
}

void Moderator::StartGame() {
    for(const auto player: players) player->AcceptCards(croupier->GetPocketCards());
    FetchFlop();
    FetchExtraCards();
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
    if(currentStage == Stage::RIVER_STAGE) {
        EndGame();
    }
    else {
        gm.didRaiseOccured = false;
        gm.whoCalledRaise = 0;
        gm.startIndex = GetFirstAliveIndex();
        //currentStage = currentStage +1;
        currentStage = static_cast<Stage>(static_cast<int>(currentStage) + 1);
        switch(currentStage) {
            case FLOP_STAGE:
                parent->SendFlop();
                break;
            case TURN_STAGE:
                parent->SendTurnCard();
                break;
            case RIVER_STAGE:
                parent->SendRiverCard();
                break;
            case END_GAME:
                break;
            default:
                break;
        }
    }
}

void Moderator::EndGame() {

}

std::vector<Player*> Moderator::FetchAllAlivePlayers() const  {
    std::vector<Player*> result;
    for(auto p: players) {
        if(p->isAlive()) result.push_back(p);
    }
    return result;
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

int Moderator::GetNewWalletForPlayer(int id) {
    return players[id]->GetMoneyLeft();
}


void Moderator::FetchExtraCards() {
    turnCard = croupier->GetTurnCard();
    riverCard = croupier->GetRiverCard();
}

struct Card Moderator::GetTurnCard() const {
    return turnCard;
}

struct Card Moderator::GetRiverCard() const {
    return riverCard;
}

void Moderator::UpdatePot(int _dp) {
    gm.totalPot += _dp;
}

int Moderator::GetPot() const {
    return gm.totalPot;
}

int Moderator::EncodeCard(struct Card &c) const {
    
}