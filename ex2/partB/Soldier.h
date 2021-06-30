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
           * Constructor of class Soldier.
           *
           * @param team - POWERLIFTERS or CROSSFITTERS.
           * @param health - life points. Must be positive.
           * @param ammo - ammunition. Must be non-negative.
           * @param range - how far can the new soldier attack. Must be positive.
           * @param power - the damage the new soldier will cause on its strikes. Must be non-negative.
           */
        Soldier(Team team,units_t health, units_t ammo, units_t range, units_t power);

        /**
           * Copy Constructor of class Soldier.
           *
           * @param other - a Soldier object to be copied.
           */
        Soldier(const  Soldier& other);

        /**
           * Destructor of class Soldier.
           */
        ~Soldier()=default;


        bool isSecondaryTarget(const GridPoint& direct_target, const GridPoint& gp) override;

        CharacterType getType() override;

        Character* clone() const override ;

        bool isMoveLegal(units_t distance) override;

        /**
           * isAttackLegal: Checks if a received cells are not too far from one another.
           *
           * @param src  - GridPoint reference of the potential attacker.
           * @param dest - GridPoint reference of the potential attack target.
           *
           * @return
           *        true  - if the distance between the two received cells is not too long.
           *        false - otherwise.
           */
        bool isAttackLegal(const GridPoint& src, const GridPoint& dest) override;

        bool isTargetLegal (const std::shared_ptr<Character>& target) override;

        /**
           * isTargetPositionLegal: Checks if the received cells are on the same row or column
           *
           * @param src  - GridPoint reference of the potential attacker.
           * @param dest - GridPoint reference of the potential attack target.
           *
           * @return
           *        true  - if src and dest are on the same row or column .
           *        false - otherwise.
           */
        bool isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) override;

        void attack(std::shared_ptr<Character>& target) override;

        void attackSecondary(std::shared_ptr<Character>& target) override;

        void reload() override;
    };
}

#endif //SOLDIER_H