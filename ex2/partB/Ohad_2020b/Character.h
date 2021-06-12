#ifndef CHARACTER_H
#define CHARACTER_H

#include "Auxiliaries.h"
#include "Matrix.h"
#include <memory>
#include <map>
/*Character is an abstract class,so can't be initialised, but still have constructor
so subclasses should init it.
*/
namespace mtm{
    class Character{
        protected:        
            Team team;
            units_t health, ammo, range, power;
            static const units_t MOVE_LIMIT;
            static const units_t RELOAD_CAPACITY;
            static const units_t ATTACK_COST = 1;
        public:
            Character(Team team, units_t health, units_t ammo, units_t range, units_t power);
            ~Character() = default;
            Character(mtm::Character const&);

            Team get_team() const;
            void healed();
            int injured(units_t injury);

            virtual void attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& src_coordinates,
             const GridPoint& dst_coordinates) = 0;
            virtual void reload() = 0;
            virtual std::string to_str() const = 0;
            virtual units_t get_move_limit() const = 0;
            virtual std::shared_ptr<Character> clone() const = 0;
    };
}

#endif
