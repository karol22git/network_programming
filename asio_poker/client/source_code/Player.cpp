#include "../include/Player.hpp"


Player::Player(unsigned int _id): id(_id), index(0){}

void Player::SetPocketCards(const std::array<struct Card, pocket_cards> & _cards) {
    pocketCards = _cards;
}

void Player::SetFlopCards(const std::array<struct Card, flop_size>& _cards) {
    flopCards = _cards;
}

void Player::Pass() {

}

void Player::Raise() {

}

void Player::Call() {

}

void Player::AddExtraCard(const struct Card& c) {
    extraCards[index] = c;
    ++index;
}