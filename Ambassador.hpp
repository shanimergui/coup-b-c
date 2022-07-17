#include "Player.hpp"
namespace coup { 
class Ambassador : public Player {
    private:
        
    public:
        Ambassador(Game& game, const std::string& name);
        void transfer(Player& from, Player& to);
        void block(Player& player);
        std::string role() const override;
};
}