#ifndef EX2_SNIPER_H
#define EX2_SNIPER_H

#include "Character.h"
#include "Auxiliaries.h"



namespace mtm{
    class Sniper: public Character
    {
        static const units_t SNIPER_MAX_MOVE=4;
        static const units_t SNIPER_CHARGE=2;
        static const units_t SNIPER_MIN_RANGE=2;
        static const units_t SNIPER_DOUBLE_POWER=2;
        units_t attack_counter=0;

    public:

        /**
           * Constructor of class Sniper.
           *
           * @param team - POWERLIFTERS or CROSSFITTERS.
           * @param health - life points. Must be positive.
           * @param ammo - ammunition. Must be non-negative.
           * @param range - how far can the new sniper attack. Must be positive.
           * @param power - the damage the new sniper will cause on its strikes. Must be non-negative.
           */
        Sniper(Team team,units_t health, units_t ammo, units_t range, units_t power);

        /**
           * Copy Constructor of class Sniper.
           *
           * @param other - a Sniper object to be copied.
           */
        Sniper(const  Sniper& other);

        /**
           * Destructor of class Sniper.
           */
        ~Sniper()=default;

        Character* clone() const override;

        CharacterType getType() override;

        /**
           * isMoveLegal: Checks if a received distance is between 0 and 4.
           *
           * @param distance - the distance of which to check validity.
           *
           * @return true  - if distance is non negative and smaller than 5.
           * @return false - otherwise.
           */
        bool isMoveLegal(units_t distance) override;

        /**
           * isAttackLegal: Checks if a received cells are not too far from one another,
           *                and not too close to one another.
           *
           * @param src  - GridPoint reference of the potential attacker.
           * @param dest - GridPoint reference of the potential attack target.
           *
           * @return true  - if the distance between the two received cells is in legal range.
           * @return false - otherwise.
           */
        bool isAttackLegal(const GridPoint& src, const GridPoint& dest) override;

        /**
           * isTargetLegal: Checks if a received cell contains a Character that is from
           *                the rival team of the caller Sniper
           *
           * @param src  - GridPoint reference of the potential attacker.
           * @param dest - GridPoint reference of the potential attack target.
           *
           * @return true  - if dest contains a Character of the opposite team.
           * @return false - otherwise.
           */
        bool isTargetLegal(const std::shared_ptr<Character>& target) override;

        bool isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) override;

        /**
           * attack: Launches an attack of the caller Sniper on the received target.
           *            If the strike number is a multiple of three, the damage to the target is doubled.
           *
           * @param target - smart pointer to the target.
           */
        void attack(std::shared_ptr<Character>& target) override;

        /**
           * reload: Increases caller Sniper's ammo by 2.
           */
        void reload() override;
    };
}


#endif //EX2_SNIPER_H
