#include "Character.h"

namespace mtm{
    Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power):
        team(team), health(health), ammo(ammo), range(range), power(power){}
    Character::Character(Character const& other): 
        team(other.team), health(other.health), ammo(other.ammo), range(other.range), power(other.power){}
    
    int Character::injured(units_t injury){
        /* 
        Injure the character, and return this->health. if health < 0 character ptr is being reseted.
        */
        this->health -= injury;
        return this->health;
    }

    void Character::healed(){
        this->health += this->power;
    }

    Team Character::get_team() const{
        return this->team;
    }


}