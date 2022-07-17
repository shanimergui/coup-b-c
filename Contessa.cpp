#include "Contessa.hpp"

using namespace coup;

Contessa::Contessa(Game& game, const std::string& name) : Player(game, name) {}

void Contessa::block(Player& player) {
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

std::string Contessa::role() const { 
    return "Contessa";
}