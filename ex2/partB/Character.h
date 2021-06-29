#ifndef CHARACTER_H
#define CHARACTER_H

#include "Auxiliaries.h"
#include <iostream>
#include <memory>
#include <list>

namespace mtm{
    class Character{

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
             * @return
             *      true - if both Characters are equal.
             *      false - otherwise.
             *
             * @throw
             *      IllegalArgument - if other is NULL
         */
        bool operator==(const Character& other);

        /**
           * Destructor of class Character.
           */
        virtual ~Character() = default;

        /**
            * getType: Returns the type of the
            * returns the derived Character type of this
        */
        virtual CharacterType getType()=0;

        /**
            * //Team getTeam() const//:
            * returns the derived Character team of this
        */
        Team getTeam() const;

        /**
            * //Character* clone() const =0//:
            * clones this (the Soldier who called the function).
            * constructs a new Soldier holding the same stats as this.
            * returns a pointer 
        */
        virtual Character* clone() const = 0;

        /**
              * //bool isMoveLegal(units_t distance)//:
              * Receives units_t parameter of distance.
              * returns true if move is legal distance- wise
              * otherwise returns false
         */
        virtual bool isMoveLegal(units_t distance)=0;

        /**
			 * //bool isAttackLegal(const GridPoint& src, const GridPoint& dest)//:
			 * receives GridPoint reference parameter of source attack and of dest of attack.
			 * returns true if attack is legal range- wise
             * otherwise returns false
		*/
        virtual bool isAttackLegal(const GridPoint& src,const GridPoint& dest)=0;

        /**
			 * //bool isTargetLegal (const std::shared_ptr<Character>& target)//:
			 * receives shared_ptr Character (reference) of target.
			 * returns true if target is legal type- wise
             * otherwise returns false
		*/
        virtual bool isTargetLegal(const std::shared_ptr<Character>& target)=0;

        /**
			 * //bool isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) override//:
			 * receives const GridPoint reference of source and destination.
			 * returns true if target position is legal direction- wise
             * otherwise returns false
		*/
        virtual bool isTargetPositionLegal(const GridPoint& src, const GridPoint& dest)=0;

        /**
            * //bool isAmmoSufficient(const std::shared_ptr<Character>& target)//:
            * receives shared_ptr Character reference (target).
            * returns true if Character's ammo is sufficient.
            * otherwise returns false
       */
        virtual bool isAmmoSufficient(const std::shared_ptr<Character>& target);

        /**
             * //void attack(std::shared_ptr<Character>& target)//: 
             * pure virtual function.
        */
        virtual void attack(std::shared_ptr<Character>& target)=0;
        /**
             * //virtual void attackSecondary(std::shared_ptr<Character>& target) 
             *  receives shared_ptr Character reference (target)
             *  if soldier is attacking creates list of secondary targets and attacks them.
             * 
        */
        virtual void attackSecondary(std::shared_ptr<Character>& target);

        /**
             * //void attack(std::list<std::shared_ptr<Character>>& secondary_targets)//: 
             *  receives list of pointers and according to demands of exercise weakens the upcoming attack.
        */
        void attack(std::list<std::shared_ptr<Character>>& secondary_targets);
        /**
             * //void hurt(units_t damage)//
             *  receives units_t damage parameter.
             *  decreases attacked characters health points according to attack.
             * if health points are negative, sets them to zero.
             * 
        */
        void hurt(units_t damage);
        /**
             * //void heal(units_t healing_points)//
             *  receives units_t healing points
             *  increases target characters health points according to rules.
        */
        void heal(units_t healing_points);
        /**
             * //bool isAlive()//
             *  returns true if character health is greater than zero
             *  otherwise returns false
        */
        bool isAlive() const;
        /**
             * //virtual void reload()=0//
             *  pure virtual reload function
        */
        virtual void reload()=0;

        /**
             * //virtual bool isSecondaryTarget(const GridPoint direct_target, const GridPoint gp)//
             *  receives two coordinates (constant GridPoint) ,initial hit point and possible secondary hitPoint.
             *  if the secondary hitPoint was hit, returns true.
             * otherwise returns false.
        */
        virtual bool isSecondaryTarget(const GridPoint& direct_target,
                                       const GridPoint& gp);

    };
}

#endif // CHARACTER_H