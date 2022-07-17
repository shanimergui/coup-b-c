#include "Duke.hpp"
using namespace coup;

const int numTeen = 10;
Duke::Duke(Game& game, const std::string& name) : Player(game, name){};

void Duke::tax() {
    this->verify_can_play();
    if (this->coins() >= numTeen) {
        throw std::logic_error("player with at least 10 coins must coup");
    }
    delete this->last_action;
    this->last_action = new Tax();
    this->last_action->execute(this);
    this->end_move();
}

void Duke::block(Player& player) {
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

std::string Duke::role() const { 
    return "Duke";
}