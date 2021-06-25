#include "Medic.h"
#include "Character.h"
#include "Auxiliaries.h"

namespace mtm{
    Medic::Medic(Team team,units_t health, units_t ammo, units_t range, units_t power):
            Character(team, health, ammo, range, power){}

    Medic::Medic(const Medic& other): mtm::Character(other.team, other.health, other.ammo, other.range, other.power){}

    Character* Medic::clone() const {
        return new Medic(*this);
    }

    CharacterType Medic::getType(){
        return MEDIC;
    }

    bool Medic::isMoveLegal(const units_t distance){
        if (distance>MEDIC_MAX_MOVE||distance<0){
            return false;
        }
        return true;
    }

    bool Medic::isAttackLegal(const GridPoint& src, const GridPoint& dest){//distance-wise
        if(GridPoint::distance(src,dest)>range){
            return false;
        }
        return true;
    }

    bool Medic::isTargetLegal(const std::shared_ptr<Character>& target){//type-wise
        if(target== nullptr || target.get() == this ){
            return false;
        }
        return true;
    }

    bool Medic::isTargetPositionLegal(const GridPoint &src, const GridPoint &dest) {
        return true;
    }

    bool Medic::isAmmoSufficient(const std::shared_ptr<Character>& target){
        if (target==nullptr||(*target).getTeam() != team){
            return ammo>=1;
        }
        return true;
    }

    void Medic::attack(std::shared_ptr<Character>& target){
        if(target->getTeam()==team){
            (*target).heal(power);
        }
        else{
            (*target).hurt(power);
            ammo--;
        }
    }

    void Medic::reload(){
        ammo+=MEDIC_CHARGE;
    }

}