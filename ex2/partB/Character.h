#ifndef EX2_CHARACTER_H
#define EX2_CHARACTER_H

#include <iostream>
#include <memory>
#include <list>
#include "Auxiliaries.h"

namespace mtm{
    class Character
    {
    protected:
        Team team;
        units_t health;
        units_t ammo;
        units_t range;
        units_t power;
    public:

        /**
           * Constructor of class Character.
           *
           * @param team - POWERLIFTERS or CROSSFITTERS.
           * @param health - life points. Must be positive.
           * @param ammo - ammunition. Must be non-negative.
           * @param range - how far can the new character attack. Must be positive.
           * @param power - the damage the new character will cause on its strikes. Must be non-negative.
           */
        explicit Character(Team team, units_t health=0, units_t ammo=0, units_t range=0, units_t power=0);

        /**
           * Copy Constructor of class Character.
           *
           * @param other - a Character object to be copied.
           */
        Character(const Character& other) = default;

        /**
           * operator= : Assignment operator of class Character.
           *
           * @param other - a Character object to be copied.
           */
        Character& operator=(const Character& other) = default;
        
        /**
           * operator== : Comparison operator.
           *              Returns whether the caller Character object starts and the Character object
           *             received by the function are equal.
           *
           * @param other - a Character to compare with the caller Character object.
           *
           * @return true - if both Characters are equal.
           * @return false - otherwise.
           *
           * @throw
           *      IllegalArgument - if other is NULL.
           */
        bool operator==(const Character& other);

        /**
           * Destructor of class Character.
           */
        virtual ~Character() = default;
        
        /**
           * getType: Returns the type of the calling Character.
           *
           * @return SOLDIER - if the calling derived object is a Soldier object.
           * @return MEDIC - if the calling derived object is a Medic object.
           * @return SNIPER - if the calling derived object is a Sniper object.
           */
        virtual CharacterType getType()=0;

        /**
           * getTeam: Returns the team of the calling Character.
           *
           * @return CROSSFITTERS - if the calling Character is on the Crossfitters team.
           * @return POWERLIFTERS - if the calling Character is on the Powerlifters team.
           */
        Team getTeam() const;
        
        /**
            * clone:  Constructs a new Character holding the same stats as the calling Character,
            *           and returns a pointer to it.
            *
            * @return
            *       A pointer to a replica of the calling Character.
            */
        virtual Character* clone() const = 0;

         /**
			* isMoveLegal: Checks if a received distance is legal for the calling Character.
            *
			* @param distance - the distance of which to check validity.
            *
			* @return true  - if distance is smaller than or equal to the Character's moving range.
            * @return false - otherwise.
		    */
        virtual bool isMoveLegal(units_t distance)=0;

         /**
			* isAttackLegal: Checks if a received cell contains a Character for which it is legal to
            *                   attack the destination cell in the matter of distance between the two,
            *                   meaning the target is not too far from the attacker nor too close to it.
			*
            * @param src  - GridPoint reference of the potential attacker.
            * @param dest - GridPoint reference of the potential attack target.
            *
			* @return true  - if attack is legal range-wise.
            * @return false - otherwise.
		    */
        virtual bool isAttackLegal(const GridPoint& src,const GridPoint& dest)=0;

        /**
           * isTargetLegal: Checks if a received cell contains a Character, for which it is legal to
           *                   attack the destination cell in the matter of type and team.
           *
           * @param src  - GridPoint reference of the potential attacker.
           * @param dest - GridPoint reference of the potential attack target.
           *
           * @return true  - if attack is legal type-wise.
           * @return false - otherwise.
           */
        virtual bool isTargetLegal(const std::shared_ptr<Character>& target)=0;

        /**
           * isTargetPositionLegal: Checks if a received cell contains a Character, for which it is legal to
           *                        attack the destination cell in the matter of direction.
           *
           * @param src  - GridPoint reference of the potential attacker.
           * @param dest - GridPoint reference of the potential attack target.
           *
           * @return true  - if attack is legal position-wise.
           * @return false - otherwise.
           */
        virtual bool isTargetPositionLegal(const GridPoint& src, const GridPoint& dest)=0;

        /**
           * isAmmoSufficient: Checks if the caller Character has enough ammunition to attack the received target.
           *
           * @param target - smart pointer to the target.
           *
           * @return true  - if the caller Character has enough ammunition to launch the attack.
           * @return false - otherwise.
           */
        virtual bool isAmmoSufficient(const std::shared_ptr<Character>& target);

        /**
           * attack: Launches an attack of the caller Character on the received target.
           *
           * @param target - smart pointer to the target.
           */
        virtual void attack(std::shared_ptr<Character>& target)=0;

        /**
           * attackSecondary: Applies the damage of the collateral damage caused by an attack
           *                    launched by a soldier to the target character.
           *
           * @param target - smart pointer to the target.
           */
        virtual void attackSecondary(std::shared_ptr<Character>& target);

        /**
           * attack: Launches an attack of the caller Character on the received target.
           *
           * @param secondary_targets - a list of smart pointers of Characters that are in range
           *                            of the collateral damage caused by an attack launched
           *                            by a soldier.
           */
        void attack(std::list<std::shared_ptr<Character>>& secondary_targets);

        /**
           * hurt: Decreases caller Character's health points by damage.
           *        If after the decrease the Character health points are negative, they are zeroed.
           *
           * @param damage - number of health points to be taken from the caller Character.
           */
        void hurt(units_t damage);

        /**
           * heal: Increases caller Character's health points by healing_points.
           *
           * @param healing_points - number of health points to be added to the caller Character.
           */
        void heal(units_t healing_points);

        /**
           * isAlive: Checks if the caller Character has more than 0 health points.
           *
           * @return true  - if the caller Character has more than 0 health points.
           * @return false - otherwise.
           */
        bool isAlive() const;

        /**
           * reload: Increases caller Character's ammo by the relevant amount according to its type.
           */
        virtual void reload()=0;

        /**
           * isSecondaryTarget: Checks if a received GridPoint (gp) is in range of collateral damage of an attack
           *                    launched on direct_target.
           *
           * @param direct_target - GridPoint of the target of the attack that was launched.
           * @param gp - GridPoint to be checked if in range of collateral damage of the attack.
           *
           * @return true  - if gp is in range of collateral damage of the attack that was launched on direct_target.
           * @return false - otherwise.
           */
        virtual bool isSecondaryTarget(const GridPoint& direct_target, const GridPoint& gp);

    };
}

#endif // CHARACTER_H