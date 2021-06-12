#include "Character.h"
#include <math.h>       /* ceil */

namespace mtm{
    class Soldier : public Character{
        private:
        static const units_t MOVE_LIMIT = 3;
        static const units_t RELOAD_CAPACITY = 3;

        public:
        Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power);
        ~Soldier() = default;
        
        units_t get_move_limit() const;
        void attack(Matrix<std::shared_ptr<Character>>& board, 
         const GridPoint& src_coordination, const GridPoint& dst_coordination);
        void collateral_attack(Matrix<std::shared_ptr<Character>>& board, 
         const GridPoint& dst_coordination);
        void reload();
        std::shared_ptr<Character> clone() const;
        std::string to_str() const;
    };
}
