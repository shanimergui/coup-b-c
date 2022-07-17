#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Game.hpp"
#include <stdexcept>

namespace coup { 

class Game;
class Action;

class Player { 

    protected:
        
        unsigned int m_coins;
        bool is_active;
        std::string name;
        Game* game; //has to be saved, at least needed to determine turn.
        Action* last_action;
        void verify_can_play();
        void end_move();


    public:
        Player(Game& game, const std::string& name);
        virtual ~Player();
        virtual void income();
        virtual void foreign_aid();
        virtual void coup(Player& player);

        unsigned int coins() const;
        virtual std::string role() const = 0;
        friend class Game;
        friend class Action;
        friend class Income;
        friend class ForeignAid;
        friend class Coup;
        friend class Tax;
        friend class Transfer;
        friend class Steal;
        friend class AssassinCoup;
        friend class Duke;
        friend class Ambassador;
        friend class Captain;
        friend class Contessa;
        
};

}
#endif
