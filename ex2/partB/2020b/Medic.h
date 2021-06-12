#include "Character.h"
#include "Exceptions.h"

namespace mtm{
    class Medic : public Character{
        private:
            static const units_t MOVE_LIMIT = 5;
            static const units_t RELOAD_CAPACITY = 5;
        public:
            Medic(Team team, units_t health, units_t ammo, units_t range, units_t power);
            ~Medic() = default;
            
            units_t get_move_limit() const;
            void attack(Matrix<std::shared_ptr<Character>>& board,
            const GridPoint& src_coordination, const GridPoint& dst_coordination);
            void heal(std::shared_ptr<Character> dst_character);
            void reload();
            std::string to_str() const;
            std::shared_ptr<Character> clone() const;
        };

    }
