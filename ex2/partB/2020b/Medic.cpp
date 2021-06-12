#include "Medic.h"


namespace mtm{
    Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power): Character(team, health, ammo, range, power){}

    units_t Medic::get_move_limit() const{
        return this->MOVE_LIMIT;
    }
    void Medic::reload() {
        this->ammo += this->RELOAD_CAPACITY;
    }
    void Medic::attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& src_coordinates,
             const GridPoint& dst_coordinates){
        /*
        Throw Exceptions:
            1. GameException::OutOfRange if the target is out attacker range.
            2. GameException::OutOfAmmo if there is not enough ammo to complete the attack.
            3. GameException::IllegalTarget if target cell is an empty cell or target is itself.
        */
        if (GridPoint::distance(src_coordinates, dst_coordinates) > this->range){
            throw OutOfRange();
        }
        else if ((board(dst_coordinates.row, dst_coordinates.col) == nullptr) or
        (src_coordinates == dst_coordinates))
        {
            throw IllegalTarget();
        }
        
        if(board(dst_coordinates.row, dst_coordinates.col)->get_team() == this->team)
        {
            this->heal(board(dst_coordinates.row, dst_coordinates.col));
        }
        
        else
        {
            if (this->ammo < Character::ATTACK_COST){
                throw OutOfAmmo();
            } 

            this->ammo -= Character::ATTACK_COST;
            int target_health = board(dst_coordinates.row, dst_coordinates.col)->injured(this->power);

            if (target_health <= 0){
                board(dst_coordinates.row, dst_coordinates.col).reset();

            }
        }
        
    }

    std::shared_ptr<Character> Medic::clone() const{
        return std::shared_ptr<Medic>(new Medic(*this));
    }

    void Medic::heal(std::shared_ptr<Character> dst_character){
        dst_character->healed();
    }

    std::string Medic::to_str() const{
        return (this->team == PYTHON) ? "m" : "M";
    }
}
