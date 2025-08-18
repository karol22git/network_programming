#include "../include/Croupier.hpp"
#include <iostream>

Croupier::Croupier(): usedCards(0), gen(rd()) {
    GenerateDeck();
}

void Croupier::GenerateDeck() {
    unsigned int index = 0 ;
    for(unsigned int i  = 1 ; i <= 4 ; ++i) {
        for(unsigned int j = 2; j <= 14 ; ++j) {
            deck[index] = struct Card(GetCardColor(i),j);
            ++index;
        }
    }
}

std::array<struct Card, 2> Croupier::GetPocketCards() {
    std::array<struct Card, 2> result;
    for(auto i: {0,1}) {
        auto a = dist(gen,decltype(dist)::param_type(0,deck_size - usedCards-1));
        result[i] = deck[a];
        Swap(a,deck_size -usedCards-1);
        ++usedCards;
    }    
    return result;
}

std::array<struct Card, 3> Croupier::GetFlop() {
    std::array<struct Card, 3> result;
    for(auto i: {0,1,2}) {
        auto a = dist(gen,decltype(dist)::param_type(2,deck_size - usedCards));
        result[i] = deck[a];
        Swap(a,deck_size -usedCards);
        ++usedCards;
    }
    return result;
}

struct Card Croupier::GetTurnCard() {
    auto a = dist(gen,decltype(dist)::param_type(2,deck_size - usedCards));
    auto result = deck[a];
    Swap(a,deck_size -usedCards);
    ++usedCards;
    return result;
}
struct Card Croupier::GetRiverCard() {
    auto a = dist(gen,decltype(dist)::param_type(2,deck_size - usedCards));
    auto result = deck[a];
    Swap(a,deck_size -usedCards);
    ++usedCards;
    return result;
}