#include "Assassin.hpp"

using namespace coup;

const int numSeven=7;
Assassin::Assassin(Game& game, const std::string& name) : Player(game, name) {}

void Assassin::coup(Player& player)
 {
    this->verify_can_play();
    delete this->last_action;
    if(m_coins>=numSeven)
    {
        this->last_action = new Coup(&player);

    }
    else
    {
        this->last_action = new AssassinCoup(&player);
    }
 
    this->last_action->execute(this);
    this->end_move();
}

std::string Assassin::role() const {
    return "Assassin";
}