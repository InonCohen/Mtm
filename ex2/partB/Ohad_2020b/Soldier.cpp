#include "Soldier.h"

namespace mtm{
    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power): Character(team, health, ammo, range, power){}
    
    units_t Soldier::get_move_limit() const{
        return this->MOVE_LIMIT;
    }

    void Soldier::attack(Matrix<std::shared_ptr<Character>>& board, 
     const GridPoint& src_coordinates, const GridPoint& dst_coordinates){
         /*
         Throw Exceptions (in this order):
            1. GameException::OutOfRange
            2. GameException::OutOfAmmo
            3. GameException::IllegalTarget
         */        
        if (GridPoint::distance(src_coordinates, dst_coordinates) > this->range){
            throw OutOfRange();
        }
        // Soldier attacks only in row/columns
        else if (this->ammo < Character::ATTACK_COST){
            throw OutOfAmmo();
        } 
        else if(!(
                (src_coordinates.row == dst_coordinates.row) or
                (src_coordinates.col == dst_coordinates.col)
                )){
             throw IllegalTarget();
        }
        //Attack
        this->ammo -= Character::ATTACK_COST;

        // If not Empty - Attack the target directly
        if (board(dst_coordinates.row, dst_coordinates.col) != nullptr){
            if (board(dst_coordinates.row, dst_coordinates.col)->get_team() != this->team){
                units_t target_health = board(dst_coordinates.row, dst_coordinates.col)->injured(this->power);
                if (target_health <= 0){
                    board(dst_coordinates.row, dst_coordinates.col).reset();
                }
            }
        }

        Soldier::collateral_attack(board, dst_coordinates);
    }
        
    void Soldier::collateral_attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& dst_coordinates){
            /* 
            Performs a colleteral attack of a soldier on a given board.
            colleteral is determined by src_coordinates+-[range/3]. 
            If a characther died in the attack - delete it from the board.
             */
            // Define sub matrix frames 
            int damage_range = int(ceil(double(this->range)/3));
            int top = (dst_coordinates.row - damage_range) < 0 ? 0 : (dst_coordinates.row - damage_range);
            int bottom = (dst_coordinates.row + damage_range) > board.height()-1 ? board.height()-1 : (dst_coordinates.row + damage_range);
            int left = (dst_coordinates.col - damage_range) < 0 ? 0 : (dst_coordinates.col - damage_range);
            int right = (dst_coordinates.col + damage_range) > board.width()-1 ? board.width()-1 : (dst_coordinates.col + damage_range);
            
            
            for(int row=top; row<=bottom;++row){
                for(int col=left; col<=right;++col){
                    /*
                    Filter out from sub matrix:
                      1. cells are far from the max distance.
                      2. empty cells
                      3. direct target
                    */
                    GridPoint current_cell = GridPoint(row, col);
                                        
                    if ((GridPoint::distance(current_cell, dst_coordinates) > damage_range) or
                        (current_cell == dst_coordinates) or
                        (board(row,col) == nullptr)){
                        continue;
                    }
                    
                    if (board(row, col)->get_team() != this->team){
                        units_t target_health = board(row,col)->injured(int(ceil(double(this->power)/2)));
                        if (target_health <= 0){
                            board(row,col).reset();
                        }
                    }    
                }
            }
        }

    void Soldier::reload() {
        this->ammo += this->RELOAD_CAPACITY;
    }

    std::shared_ptr<Character> Soldier::clone() const{
        return std::shared_ptr<Soldier>(new Soldier(*this));
    }

    std::string Soldier::to_str() const{
        return (this->team == PYTHON) ? "s" : "S";
    }
}