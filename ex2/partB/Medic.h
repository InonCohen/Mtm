#ifndef MEDIC_H
#define MEDIC_H
#include "Auxiliaries.h"
#include "Character.h"




namespace mtm{
    class Medic: public Character{
        static const units_t MEDIC_MAX_MOVE=5;
        static const units_t MEDIC_CHARGE=5;
    public:

        /**
           * Constructor of class Medic.
           *
           * @param team - POWERLIFTERS or CROSSFITTERS.
           * @param health - life points. Must be positive.
           * @param ammo - ammunition. Must be non-negative.
           * @param range - how far can the new medic attack. Must be positive.
           * @param power - the damage the new medic will cause on its strikes. Must be non-negative.
           */
        Medic(Team team,units_t health, units_t ammo, units_t range, units_t power);

        /**
           * Copy Constructor of class Medic.
           *
           * @param other - a Medic object to be copied.
           */
        Medic(const Medic& other);

        /**
           * Destructor of class Medic.
           */
        ~Medic()=default;

        CharacterType getType() override;

        bool isMoveLegal(units_t distance) override;//distance-wise

        bool isAttackLegal(const GridPoint& src, const GridPoint& dest) override;//range-wise

        bool isTargetLegal (const std::shared_ptr<Character>& target) override;//type-wise

        bool isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) override;//direction-wise

        bool isAmmoSufficient(const std::shared_ptr<Character>& target) override;

        void attack(std::shared_ptr<Character>& target) override;

        void reload() override;

        Character* clone() const override;
    };
}


#endif //MEDIC_H
