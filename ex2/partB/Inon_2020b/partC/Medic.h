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
            * //Medic(Team team,units_t health, units_t ammo, units_t range, units_t power)//:
            * Medic constructor.
            * receives Medic Team(Powerlifters or Crossfitters), positive integer health,
                    non-negative integers ammo, range, power.
            * constructs medic, by creating Character with the params given.
     */
        Medic(Team team,units_t health, units_t ammo, units_t range, units_t power);
    /**
            * //Medic(const Medic& other)//:
            * Medic copy constructor.
            * receives a Medic reference
            * constructs a new Medic holding the same stats of other.
     */    
        Medic(const Medic& other);

    /**
            * //~Medic()=default//:
            * Medic default destructor
            * destroys Medic
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
