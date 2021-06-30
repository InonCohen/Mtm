#ifndef EX2_MEDIC_H
#define EX2_MEDIC_H
#include "Auxiliaries.h"
#include "Character.h"


namespace mtm{
    class Medic: public Character
    {
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

        /**
           * isMoveLegal: Checks if a received distance is between 0 and 5.
           *
           * @param distance - the distance of which to check validity.
           *
           * @return true  - if distance is non negative and smaller than 6.
           * @return false - otherwise.
           */
        bool isMoveLegal(units_t distance) override;

        /**
           * isAttackLegal: Checks if a received cells are not too far from one another.
           *
           * @param src  - GridPoint reference of the potential attacker.
           * @param dest - GridPoint reference of the potential attack target.
           *
           * @return true  - if the distance between the two received cells is not too long.
           * @return false - otherwise.
           */
        bool isAttackLegal(const GridPoint& src, const GridPoint& dest) override;

        /**
           * isTargetLegal: Checks if a received cell contains a Character, and that the two cells are different.
           *
           * @param src  - GridPoint reference of the potential attacker.
           * @param dest - GridPoint reference of the potential attack target.
           *
           * @return true  - if dest contains a Character that is not the caller Medic.
           * @return false - otherwise.
           */
        bool isTargetLegal (const std::shared_ptr<Character>& target) override;

        bool isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) override;

        bool isAmmoSufficient(const std::shared_ptr<Character>& target) override;

        /**
           * attack: If the target is a Character that is on the same team as the caller Medic,
           *            the target is healed by Medic. Otherwise, the target is attacked by Medic.
           *
           * @param target - smart pointer to the target.
           */
        void attack(std::shared_ptr<Character>& target) override;

        /**
           * reload: Increases caller Medic's ammo by 5.
           */
        void reload() override;

        Character* clone() const override;
    };
}


#endif //EX2_MEDIC_H
