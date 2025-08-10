#include "../include/Player.hpp"

Player* Player::instance = nullptr;
Player::Player(unsigned int _id): id(_id), index(0), moneyLeft(0) {}

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

Player& Player::GetInstance() {
    //static Player instance(id);
    return *instance;
}

void Player::Init(unsigned int id) {
    instance = new Player(id);
}

unsigned int Player::GetId() const {
    return id;
}

void Player::SetMoneyLeft(int _money) {
    moneyLeft = _money;
}