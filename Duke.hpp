#include "Player.hpp"
namespace coup {

class Duke : public Player {
    public:
        Duke(Game& game, const std::string& name); //constructor
        void tax();
        void block(Player& player);
        std::string role() const override; //each player has his own role and therefore we do "override"
        friend class Tax;
};
}