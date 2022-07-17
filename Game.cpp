#include "Game.hpp"
#include <iostream>
using namespace coup;

const int numSix = 6;
Game::Game() {
    this->turn_index = 0;
    this->is_running = false;
}

void Game::add_player(Player& player) {
    if (this->is_running){
        throw std::logic_error("can not add player, game is already running");
    }
    if (this->m_players.size() >= numSix) {
        throw std::logic_error("Game cannot contain more than 6 players");
    }
        player.is_active = true;
        this->m_players.push_back(&player);
    
    
}

std::vector<std::string> Game::players() const {
    std::vector<std::string> player_names;
    for (const Player* const player: this->m_players ) {
        if (player->is_active) {
            player_names.push_back(player->name);
        }
    }
    return player_names;
}

/**
 * when dealing with something circular with size we use a module of the number of players in the game.
 * 3 players
 * 0+1%3 = 1
 * 1+1%3 = 2 
 * 2+1%3 = 3
 */

void Game::switch_to_next_turn() {
    this->is_running = true;
    bool found = false;
    size_t index = this->turn_index + 1;
    while (!found) {
        if (this->m_players[index % m_players.size()]->is_active) {
            found = true;
            this-> turn_index = index % m_players.size();
        }
        else {
            index++;
        }
    }
}

bool Game::can_player_play(Player* player) {   
    return this->count_active_players() > 1 && (player == this->m_players[turn_index]); 
}
std::string Game::turn() const {
    Player* player = this->m_players[this->turn_index];
    std::string name = player->name;
    return name;
}

std::string Game::winner() const { 
    if (this->count_active_players() > 1 || !this->is_running) {
        throw std::logic_error("the game is not over, no winner yet");
    }
    std::string winner;
    for (const Player* const player: this->m_players ) {
        if (player->is_active) {
            winner = player->name;
        }
    }
    return winner;
}

size_t Game::count_active_players() const {
    size_t active = 0;
    for (const Player* const player: this->m_players ) {
        if (player->is_active) {
            active++;
        }
    }
    return active;
}


Action::~Action() {}

void Income::execute(Player* player) {
    player->m_coins++;
}

void Income::undo(Player* blocker, Player* blocked) {
    throw std::logic_error("income can not be blocked");
}

void ForeignAid::execute(Player* player) {
    player->m_coins+=2;
}

void ForeignAid::undo(Player* blocker, Player* blocked) {
    if (blocker->role() == "Duke") {
        blocked->m_coins-=2;
        blocked->last_action = nullptr;
    }
    else {
        throw std::logic_error("Only duke can block foreign aid");
    }
}

Coup::Coup(Player* player_to_kill) { 
    this->player_to_kill = player_to_kill;
}

const int numSeven = 7;
void Coup::execute(Player* player) {
    if (player->m_coins >= numSeven && this->player_to_kill->is_active) {
        player->m_coins -= numSeven;
        this->player_to_kill->is_active = false;
    }
    else {
        throw std::logic_error("coup can not be done");
    }   
}

void Coup::undo(Player* blocker, Player* blocked) {
    throw std::logic_error("No one can block regular coup");
    
}

void Tax::execute(Player* player) {
    player->m_coins += 3;
}

void Tax::undo(Player* blocker, Player* blocked) {
    throw std::logic_error("duke tax can not be blocked");
}

AssassinCoup::AssassinCoup(Player* player_to_kill) {
    this->player_to_kill = player_to_kill;
}

void AssassinCoup::execute(Player* player) {
    unsigned int cost=3;
    if (player->coins() >= cost && this->player_to_kill->is_active ) {
        player->m_coins-=cost;
        this->player_to_kill->is_active = false;
    }
    else {
        throw std::logic_error("coup can not be done");
    }
}


void AssassinCoup::undo(Player* blocker, Player* blocked) {
    if (blocker->role() == "Contessa") {
        this->player_to_kill->is_active = true;
        this->player_to_kill->last_action = nullptr;
    }
    else {
        throw std::logic_error("only contessa can block assassin");
    }
}

Transfer::Transfer(Player* from, Player* to) {
    this->from = from;
    this->to = to;
}

void Transfer::execute(Player* player) {
    if (this->from->coins() > 0) { 
        this->to->m_coins++;
        this->from->m_coins--;
    }
    else {
        throw std::logic_error("ambassador can not steal from one who has no coins");
    }
}

void Transfer::undo(Player* blocker, Player* blocked) {
    throw std::logic_error("no one can block ambassador transfer");
}

Steal::Steal(Player* from) { 
    this->from = from;
}

void Steal::execute(Player* player) {
    if (this->from->coins() >= 2) {
        player->m_coins+=2;
        this->from->m_coins -= 2;
    }
    else {
        player->m_coins += this->from->m_coins;
        this->from->m_coins = 0;
        // throw std::logic_error("can not steal 2 coins, player does not have enough coins");
    }
}

void Steal::undo(Player* blocker, Player* blocked) {
    if (blocker->role() == "Captain" || blocker->role() == "Ambassador") {
        this->from->m_coins += 2;
        blocked->m_coins -= 2;
    }
    else { 
        throw std::logic_error("only captain or ambassador can block steal");
    }
}