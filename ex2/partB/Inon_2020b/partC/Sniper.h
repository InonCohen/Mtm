#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"
#include "Auxiliaries.h"



namespace mtm{
    class Sniper: public Character{
        static const units_t SNIPER_MAX_MOVE=4;
        static const units_t SNIPER_CHARGE=2;
        static const units_t SNIPER_MIN_RANGE=2;
        static const units_t SNIPER_DOUBLE_POWER=2;
        units_t attack_counter=0;
    public:
        /**
            * //Sniper(Team team,units_t health, units_t ammo, units_t range, units_t power)//:
            * Sniper constructor.
            * receives Sniper's Team(Powerlifters or Crossfitters), positive integer health,
                    non-negative integers ammo, range, power.
            * constructs Sniper, by creating Character with the params given.
     */
        Sniper(Team team,units_t health, units_t ammo, units_t range, units_t power);
         /**
            * //Sniper(const  Soldier& other)//:
            * Sniper copy constructor.
            * receives a sniper's reference
            * constructs a new Sniper holding the same stats of other.
     */    
        Sniper(const  Sniper& other);
        /**
            * //~Sniper()=default//:
            * Sniper default destructor
            * destroys Sniper
      */
        ~Sniper()=default;
        Character* clone() const override;
        CharacterType getType() override;
        bool isMoveLegal(units_t distance) override;
        bool isAttackLegal(const GridPoint& src, const GridPoint& dest) override;
        bool isTargetLegal(const std::shared_ptr<Character>& target) override;
        bool isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) override;
        void attack(std::shared_ptr<Character>& target) override;
        void reload() override;
    };
}


#endif //SNIPER_H
