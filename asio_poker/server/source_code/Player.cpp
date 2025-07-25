#include "../include/Player.hpp"


Player::Player(unsigned int _id): id(_id) {

}

void Player::AcceptCards(std::array<struct Card, pocket_cards> pocketCards) {
    cards = pocketCards;
}

std::array<struct Card, pocket_cards> Player::GetPocketCards() const {
    return cards;
}

unsigned int Player::GetId() const {
    return id;
}