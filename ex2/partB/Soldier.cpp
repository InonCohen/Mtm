#include <cmath>
#include "Soldier.h"
#include "Auxiliaries.h"
#include "Character.h"
#include "Exceptions.h"

namespace mtm{

    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power) :
            Character(team, health, ammo, range, power) {}

    Soldier::Soldier(const Soldier& other): Character(other.team, other.health, other.ammo, other.range, other.power){}

    Character* Soldier::clone() const
    {
        return new Soldier(*this);
    }

    CharacterType Soldier::getType()
    {
        return SOLDIER;
    }

    bool Soldier::isMoveLegal(const units_t distance)
    {
        if (distance>SOLDIER_MAX_MOVE||distance<0){
            return false;
        }
        return true;
    }

    bool Soldier::isAttackLegal(const GridPoint& src, const GridPoint& dest)
    {
        if(GridPoint::distance(src, dest)>range){
            return false;
        }
        return true;
    }

    bool Soldier::isTargetLegal(const std::shared_ptr<Character>& target)
    {
        return true;
    }

    bool Soldier::isTargetPositionLegal(const GridPoint &src, const GridPoint &dest)
    {
        if (src.row!=dest.row && src.col!=dest.col){
            return false;
        }
        return true;
    }

    void Soldier::attack(std::shared_ptr<Character>& target)
    {
        if(target!= nullptr&&(*target).getTeam()!=team){
            (*target).hurt(power);
        }
        ammo--;
    }

    void Soldier::attackSecondary(std::shared_ptr<Character>& target)
    {
        if((*(target)).getTeam()!=team) {
            (*target).hurt(ceil(double(power) / SOLDIER_SECONDARY_EFFECT));
        }
    }

    bool Soldier::isSecondaryTarget(const GridPoint& initial_hit_point, const GridPoint& possible_secondary_hit_point)
    {
        int distance_from_direct_target=GridPoint::distance(possible_secondary_hit_point,initial_hit_point);
        return  ((0 < distance_from_direct_target) &&
                 (distance_from_direct_target <= ceil(double(range)/SOLDIER_SECONDARY_RANGE)));
    }

    void Soldier::reload()
    {
        ammo+=SOLDIER_CHARGE;
    }

}