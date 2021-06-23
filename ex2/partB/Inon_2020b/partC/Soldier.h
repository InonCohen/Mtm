#ifndef SOLDIER_H
#define SOLDIER_H

#include "Auxiliaries.h"
#include "Character.h"

namespace mtm{
    class Soldier: public Character{
        static const units_t SOLDIER_MAX_MOVE=3;
        static const units_t SOLDIER_CHARGE=3;
        static const units_t SOLDIER_SECONDARY_RANGE=3;
        static const units_t SOLDIER_SECONDARY_EFFECT=2;
    public:
    /**
            * //Soldier(Team team,units_t health, units_t ammo, units_t range, units_t power)//:
            * Soldier constructor.
            * receives Soldier's Team(Powerlifters or Crossfitters), positive integer health,
                    non-negative integers ammo, range, power.
            * constructs Soldier, by creating Character with the params given.
     */
        Soldier(Team team,units_t health, units_t ammo, units_t range, units_t power);
    /**
            * //Soldier(const  Soldier& other)//:
            * Soldier copy constructor.
            * receives a soldier's reference
            * constructs a new Soldier holding the same stats of other.
     */    
        Soldier(const  Soldier& other);
     /**
            * //~Soldier()//:
            * - Soldier's default destructor
            * destroys Soldier
      */
        ~Soldier()=default;

        bool isSecondaryTarget(const GridPoint initial_hit_point, const GridPoint possible_secondary_hit_point) override;
        CharacterType getType() override;
        Character* clone() const override ;
        bool isMoveLegal(units_t distance) override;
        bool isAttackLegal(const GridPoint& src, const GridPoint& dest) override;
        bool isTargetLegal (const std::shared_ptr<Character>& target) override;
        bool isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) override;
        void attack(std::shared_ptr<Character>& target) override;
        void attackSecondary(std::shared_ptr<Character>& target) override;
        void reload() override;
    };
}

#endif //SOLDIER_H