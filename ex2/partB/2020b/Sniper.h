#include "Character.h"
#include <math.h>       /* ceil */
#include <memory>

namespace mtm{
    class Sniper : public Character{
        private:
        static const units_t MOVE_LIMIT = 4;
        static const units_t RELOAD_CAPACITY = 2;
        int attack_counter = 1;
        public:
        Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power);
        ~Sniper() = default;
        
        units_t get_move_limit() const;
        void reload();
        void attack(Matrix<std::shared_ptr<Character>>& board, 
         const GridPoint& src_coordination, const GridPoint& dst_coordination);
        std::shared_ptr<Character> clone() const;
        std::string to_str() const;
    };
}
