#include "Sniper.h"
#include "Auxiliaries.h"

namespace mtm{
    Sniper::Sniper(Team team,units_t health, units_t ammo, units_t range, units_t power):
    Character(team, health, ammo, range, power){}

    Sniper::Sniper(const Sniper& other): Character(other.team, other.health, other.ammo, other.range, other.power){}

    Character* Sniper::clone() const {
        return new Sniper(*this);
    }

    CharacterType Sniper::getType(){
        return SNIPER;
    }

    bool Sniper::isMoveLegal(const units_t distance){//distance-wise
        if (distance>SNIPER_MAX_MOVE||distance<0){
            return false;
        }
        return true;
    }

    bool Sniper::isAttackLegal(const GridPoint& src, const GridPoint& dest){//range-wise
        units_t min_range=ceil(double(range)/SNIPER_MIN_RANGE);
        units_t distance=GridPoint::distance(src,dest);
        if(distance<min_range||distance>range){
            return false;
        }
        return true;
    }

    bool Sniper::isTargetLegal(const std::shared_ptr<Character>& target){//type-wise
        if(target == nullptr || ((target).get())->getTeam()== team){
            return false;
        }
        return true;
    }

    bool Sniper::isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) {
        return true;
    }

    void Sniper::attack(std::shared_ptr<Character>& target){
        if(attack_counter==SNIPER_DOUBLE_POWER){
            (target.get())->hurt(power*SNIPER_DOUBLE_POWER);
            attack_counter=0;
        }
        else {
            (target.get())->hurt(power);
            attack_counter++;
        }
        ammo--;
    }

    void Sniper::reload(){
        ammo+=SNIPER_CHARGE;
    }

}