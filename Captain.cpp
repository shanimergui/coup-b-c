#include "Captain.hpp"

using namespace coup;

Captain::Captain(Game& game, const std::string& name) : Player(game, name) {}

void Captain::block(Player& player) {
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

void Captain::steal(Player& from) {
    this->verify_can_play();
    delete this->last_action;
    this->last_action = new Steal(&from);
    this->last_action->execute(this);
    this->end_move();
}

std::string Captain::role() const {
    return "Captain";
}
