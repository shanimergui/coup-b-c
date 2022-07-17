#include "Player.hpp"
#include <iostream>
using namespace coup;

const int numTeen = 10;
Player::Player(Game& game, const std::string& name) {
    this->game = &game;
    this->name = name;
    this->m_coins = 0; 
    this->is_active = false;
    this->last_action = nullptr;
    this->game->add_player(*this);
}

Player::~Player() { 
    if (this->last_action != nullptr) {
        delete this->last_action;
        this->last_action = nullptr;
    }
}

void Player::income() {
    this->verify_can_play();
    if (this->coins() >= numTeen) {
        throw std::logic_error("player with 10 or more coins should coup only");
    }
    delete this->last_action;
    this->last_action = new Income();
    this->last_action->execute(this);
    this->end_move();
}

void Player::foreign_aid() {
    this->verify_can_play();
    if (this->coins() >= numTeen) {
        throw std::logic_error("player with 10 or more coins should coup only");
    }
    delete this->last_action;
    this->last_action = new ForeignAid();
    this->last_action->execute(this);
    this->end_move();
}

void Player::coup(Player& player) {
    this->verify_can_play();
    delete this->last_action;
    this->last_action = new Coup(&player);
    this->last_action->execute(this);
    this->end_move();
}

unsigned int Player::coins() const {
    return this->m_coins;
}
void Player::verify_can_play() {
    if (!this->game->can_player_play(this)) {
        throw std::logic_error("player trying to play not on his turn");
    }
}

void Player::end_move() {
    this->game->switch_to_next_turn();
}
