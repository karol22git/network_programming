#include "../include/Moderator.hpp"
#include "../include/UdpServer.hpp"
#include "../poker_engine/omp/HandEvaluator.h"
using namespace omp;
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
        std::vector<int> winners;
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
                parent->BroadcastCards();
                //winners = GetWinners();
                //parent->Send
                break;
            default:
                break;
        }
    }
}
void Moderator::EndGame() {
    parent->BroadcastCards();
    auto winners = GetWinners();
    if(winners.size() == 1) parent->BroadcastWinner(winners[0]);
    else parent->BroadcastWinners(winners);
}
//std::vector<int> Moderator::GetWinners() const {
//    auto survivors = FetchAllAlivePlayers();
//    struct winnerMetadata {
//        int winnerId = 0;
//        int winnerScore = 0;
//        std::vector<int> winnersIds;
//    };
//    struct winnerMetadata wm;
//    HandEvaluator eval;
//    auto sharedCards = CardsToVector();
//    for(const auto& survivor: survivors) {
//        Hand h = Hand::empty();
//        auto pocketCards = survivor->GetPockedCards();
//        for(const auto card: sharedCards) h+= Hand(card.toInt());
//        for(const auto card: pocketCards) h+= Hand(card.toInt());
//        auto result = eval.evaluate(h);
//        if(result == wm.winnerScore) {
//            wm.winnerScore = result;
//            wm.winnerId = survivor.id;
//            winnersIds.push_back(survivor->GetId());
//        }
//        else if(result > wm.winnerScore) {
//            wm.winnersIds.clear();
//            wm.winnersIds.push_back(survivor->GetId());
//            wm.winnerScore = result;
//        }
//    }
//    return wm.winnersIds;
//}
std::vector<int> Moderator::GetWinners() const {
    auto survivors = FetchAllAlivePlayers();

    struct WinnerMetadata {
        int winnerScore = 0;
        std::vector<int> winnersIds;
    };

    WinnerMetadata wm;
    HandEvaluator eval;
    auto sharedCards = CardsToVector();

    for (const auto& survivor : survivors) {
        Hand h = Hand::empty();
        auto pocketCards = survivor->GetPocketCards(); // poprawiona literówka

        for (const auto& card : sharedCards)
            h += Hand(card.toInt());

        for (const auto& card : pocketCards)
            h += Hand(card.toInt());

        int result = eval.evaluate(h);

        if (result == wm.winnerScore) {
            wm.winnersIds.push_back(survivor->GetId());
        }
        else if (result > wm.winnerScore) {
            wm.winnerScore = result;
            wm.winnersIds.clear();
            wm.winnersIds.push_back(survivor->GetId());
        }
    }
    return wm.winnersIds;
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
/*
 0 - spades = pik
1 - hearts - kier
2 - clubs - trefl
3 - diamonds - karo

*/


std::vector<struct Card> Moderator::CardsToVector() const {
    std::vector<struct Card> result;
    if(currentStage >= Stage::FLOP_STAGE) {
        for(const auto&  card: flopCards) result.push_back(card);
    }
    if(currentStage >= Stage::TURN_STAGE) result.push_back(turnCard);
    if(currentStage >= Stage::RIVER_STAGE) result.push_back(riverCard);
    return result;
}