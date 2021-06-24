#include "Auxiliaries.h"
#include "Character.h"

namespace mtm {

    Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power):
    team(team), health(health), ammo(ammo), range(range), power(power){}

    Character::Character(const Character& other):
    team(other.team), health(other.health), ammo(other.ammo), range(other.range), power(other.power){}

    Character& Character::operator=(const Character& other){
        team=other.team;
        health=other.health;
        ammo=other.ammo;
        range=other.range;
        power=other.power;
        return *this;
    }

    Team Character::getTeam() const {
        return team;
    }


//    Team Character::getTeam(const std::shared_ptr<Character>& ptr_to_self) const {
//        if(ptr_to_self!= nullptr) {
//            return this->team;
//        }
//    }

    bool Character::operator==(const Character& other){
        if(team!=other.team||health!=other.health||ammo!=other.ammo||range!=other.range||power!=other.power){
            return false;
        }
        return true;
    }

    bool Character::isAmmoSufficient(const std::shared_ptr<Character>& target) {
        return (ammo >= 1);
    }

    void Character::hurt(units_t damage){
        health-=damage;
        if(health<=0){
            health=0;
        }
    }

    void Character::heal(units_t healing_points){
        health+=healing_points;
    }

   bool Character::isAlive() {
        if(health<=0){
            return false;
        }
        return true;
    }

    void Character::attack(std::list<std::shared_ptr<Character>>& secondary_targets){
        while(!secondary_targets.empty()){
            this->attackSecondary(secondary_targets.front());
            secondary_targets.pop_front();
        }
    }

    bool Character::isSecondaryTarget(const GridPoint initial_hit_point, const GridPoint possible_secondary_hit_point){
        return false;
    }



    void Character::attackSecondary(std::shared_ptr<Character>& target){
        return;
    }

}