#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "Player.hpp"

namespace coup {
    class Player;

    class Game {
        private:
            size_t turn_index ; //turn who to play.
            bool is_running; //holds whether the game is running or not.(a player cannot join if the game has started)
            std::vector<Player*> m_players; //pointer of name of all player.
            void add_player(Player& player); //adding a player
            size_t count_active_players() const; //how many active players do i have(we will need this function  to be 1 to get a winner).
            void switch_to_next_turn(); //moves the turn to the next active play.
            bool can_player_play(Player* player); //if the player not in his turn we will thorw an exception.
        public:
            Game();
            std::vector<std::string> players() const;
            std::string turn() const;
            std::string winner() const;
    
            friend class Player; 
    };


/**
 * class Action - to save a pointer ti=o the move.
 * in each player we keep a pointer to the lase action.
 * a player can do an income action or a coup action, 
 * and we do not know what he will do so we will save a variable that will save the last move. 
 * will save what the last action a player did.
 */
    class Action {
        public:
            virtual void execute(Player* player) = 0;
            virtual void undo(Player* blocker, Player* blocked) = 0;
            virtual ~Action();
    };

    class Income : public Action { 
        public:
            void execute(Player* player) override;
            void undo(Player* blocker, Player* blocked) override;
    };

    class ForeignAid : public Action {
        public:
            void execute(Player* player) override;
            void undo(Player* blocker, Player* blocked) override;
    };

    class Coup : public Action {
        private:
            Player* player_to_kill;
        public:
            Coup(Player* player_to_kill);
            void execute(Player* player) override;
            void undo(Player* blocker, Player* blocked) override;
    };

    class Tax : public Action {
        public:
            void execute(Player* player) override;
            void undo(Player* blocker, Player* blocked) override;
    };

    class AssassinCoup : public Action {
        private:
            Player* player_to_kill;
        public:
            AssassinCoup(Player* player_to_kill);
            void execute(Player* player) override;
            void undo(Player* blocker, Player* blocked) override;
    };

    class Transfer : public Action {
        private:
            Player* from;
            Player* to;
        public:
            Transfer(Player* from, Player* to);
            void execute(Player* player) override;
            void undo(Player* blocker, Player* blocked) override;
    };

    class Steal : public Action {
        private: 
            Player* from;
        public:
            Steal(Player* from);
            void execute(Player* player) override;
            void undo(Player* blocker, Player* blocked) override;
    };


}

#endif