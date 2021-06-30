#include "Auxiliaries.h"
#include "Character.h"

namespace mtm {

    Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power):
            team(team), health(health), ammo(ammo), range(range), power(power){}

    Team Character::getTeam() const
    {
        return team;
    }

    bool Character::operator==(const Character& other)
    {
        if(team!=other.team||health!=other.health||ammo!=other.ammo||range!=other.range||power!=other.power){
            return false;
        }
        return true;
    }

    bool Character::isAmmoSufficient(const std::shared_ptr<Character>& target)
    {
        return (ammo >= 1);
    }

    void Character::hurt(units_t damage)
    {
        health-=damage;
        if(health<=0){
            health=0;
        }
    }

    void Character::heal(units_t healing_points)
    {
        health+=healing_points;
    }

    bool Character::isAlive() const
    {
        return health>0;
    }

    void Character::attack(std::list<std::shared_ptr<Character>>& secondary_targets)
    {
        while(!secondary_targets.empty()){
            this->attackSecondary(secondary_targets.front());
            secondary_targets.pop_front();
        }
    }

    bool Character::isSecondaryTarget(const GridPoint& direct_target,const GridPoint& gp)
    {
        return false;
    }

    void Character::attackSecondary(std::shared_ptr<Character>& target){}
}