#include "Ambassador.hpp"
using namespace coup;

const int numTeen = 10;

Ambassador::Ambassador(Game& game, const std::string& name) : Player(game, name) {}

void Ambassador::transfer(Player& from, Player& to) {
    this->verify_can_play();
    if (this->coins() >= numTeen) {
        throw std::logic_error("player with 10 or more coins should coup only");
    }
    delete this->last_action;
    this->last_action = new Transfer(&from, &to);
    this->last_action->execute(this);
    this->end_move();
}

void Ambassador::block(Player& player) {
    if (!this->is_active) {
        throw std::logic_error("Player who is not active can't block");
    }
    if (player.last_action == nullptr) {
        throw std::logic_error("the player has no move to block");
    }
    player.last_action->undo(this, &player);
    delete player.last_action;
    player.last_action = nullptr;
}

std::string Ambassador::role() const {
    return "Ambassador";
}