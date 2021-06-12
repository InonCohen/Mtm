#include "Sniper.h"

namespace mtm{
    Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power): Character(team, health, ammo, range, power){}
    
    units_t Sniper::get_move_limit() const{
        return this->MOVE_LIMIT;
    }

    void Sniper::reload() {
        this->ammo += this->RELOAD_CAPACITY;
    }
    
    std::shared_ptr<Character> Sniper::clone() const{
        return std::shared_ptr<Sniper>(new Sniper(*this));

    }

    void Sniper::attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& src_coordinates,
            const GridPoint& dst_coordinates){
    /*
    Throw Exceptions:
        1. GameException::OutOfRange if the target is not in the allowed range: range/2 <= target <= range.
        2. GameException::OutOfAmmo if there is not enough ammo to complete the attack.
        3. GameException::IllegalTarget if target cell is an empty cell or from the same team.
    */
    if (!(GridPoint::distance(src_coordinates, dst_coordinates) >= ceil(double(range)/2) and
     GridPoint::distance(src_coordinates, dst_coordinates) <= this->range)){
        throw OutOfRange();
    }
    if (this->ammo < Character::ATTACK_COST){
        throw OutOfAmmo();
    } 

    if (board(dst_coordinates.row, dst_coordinates.col) == nullptr){
        throw IllegalTarget();
    }
    else if (board(dst_coordinates.row, dst_coordinates.col)->get_team() == this->team)
    {
        throw IllegalTarget();
    }


    // finally, make damage!
    this->ammo -= Character::ATTACK_COST;
    int current_power = this->power;
    if (this->attack_counter % 3 == 0 and this->attack_counter != 0){
        current_power = 2*this->power;
    }
    int target_health = board(dst_coordinates.row, dst_coordinates.col)->injured(current_power);
    if((target_health) <= 0){
        board(dst_coordinates.row, dst_coordinates.col).reset();
    }
    this->attack_counter++;
}
    
    std::string Sniper::to_str() const{
        return (this->team == PYTHON) ? "n" : "N";
    }
}