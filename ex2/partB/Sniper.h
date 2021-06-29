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

        bool isMoveLegal(units_t distance) override;

        bool isAttackLegal(const GridPoint& src, const GridPoint& dest) override;

        bool isTargetLegal(const std::shared_ptr<Character>& target) override;

        bool isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) override;

        void attack(std::shared_ptr<Character>& target) override;

        void reload() override;
    };
}


#endif //SNIPER_H
