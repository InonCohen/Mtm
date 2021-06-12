#include "Game.h"
using std::cout;
using std::endl;


namespace mtm{
Game::Game(int height, int width){
    /*Throw Exceptions:
        1. GameException::IllegalArgument if dimension isn't a positive integer.
    */
    if (!(height > 0 and width > 0)){
        throw IllegalArgument();
    }
    board = Matrix<std::shared_ptr<Character>>(Dimensions(height, width));
}

Game& Game::operator= (const Game &other){
    if (this == &other){
        return *this;
    }

    this->board = Matrix<std::shared_ptr<Character>> (other.board);

    return *this;
}

std::shared_ptr<Character> Game::makeCharacter(CharacterType type,
    Team team, units_t health, units_t ammo, units_t range, units_t power){
    /*Throw Exception:
        1. GameException::IllegalArgument if health isn't bigger than zero or if any other parameter is non-positive.
    */
    if (!(health > 0) or !((ammo >= 0) and (range >= 0) and (power >= 0))){
            throw IllegalArgument();
        }
    std::shared_ptr<Character> character;
    if (type == SOLDIER){
        character = std::shared_ptr<Character>(new Soldier(team, health, ammo, range, power));
    }
    else if (type == MEDIC){
        character = std::shared_ptr<Character>(new Medic(team, health, ammo, range, power));

    }
    else if (type == SNIPER){
        character = std::shared_ptr<Character>(new Sniper(team, health, ammo, range, power));
    }
    
    return character;
}

void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character){
    /*
    Throwing Excetions:
        1. IllegalCell if point is not on the game grid.
        2. CellOccupied if there is already a caharcter in the requested location.
    */
    if (coordinates.row >= this->board.height() or coordinates.col >= this->board.width() or
    (coordinates.row < 0 or coordinates.col < 0)){
        throw IllegalCell();
        }
    else if(this->board(coordinates.row, coordinates.col) != nullptr){
        throw CellOccupied();
    }
    board(coordinates.row, coordinates.col) = character;
}

void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
    /*
    Throw Exceptions:
        1. GameException::IllegalCell if coordinations are out of grid.
        2. GameException::CellEmpty if in src_coordinates is no charecter to move.
        3. GameException::MoveTooFar if character is requested to move more than its limit.
        4. GameException::CellOccupied if dst_coordinates is occuipied.

    */
    if ((src_coordinates.row >= this->board.height() or src_coordinates.col >= this->board.width())
            or (dst_coordinates.row >= this->board.height() or dst_coordinates.col >= this->board.width())
            or (src_coordinates.row < 0 or src_coordinates.col < 0)
            or (dst_coordinates.row < 0 or dst_coordinates.col < 0))
            {
        throw IllegalCell();
        }
        else if(this->board(src_coordinates.row, src_coordinates.col) == nullptr){
            throw CellEmpty();
        }

    std::shared_ptr<Character> src_ptr = this->board(src_coordinates.row, src_coordinates.col);
    std::shared_ptr<Character> dst_ptr = this->board(dst_coordinates.row, dst_coordinates.col);

    if (GridPoint::distance(src_coordinates, dst_coordinates) > src_ptr->get_move_limit()){
        throw MoveTooFar();
    }
    else if (dst_ptr != nullptr){
        throw CellOccupied();
    }

    this->board(dst_coordinates.row, dst_coordinates.col) = this->board(src_coordinates.row, src_coordinates.col)->clone();
    this->board(src_coordinates.row, src_coordinates.col).reset();
    }

void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
    /*
    Throw Exceptions:
        1. GameException::IllegalCell if coordinations are out of grid.
        2. GameException::CellEmpty if in src_coordinates is no charecter to reload.
        3. GameException::OutOfRange if the target is out attacker range.
        4. GameException::OutOfAmmo if there is not enough ammo to complete the attack.
        5. GameException::IllegalTarget if target cell is an empty cell.
        6. mtm::Matrix::AccessIllegalElement
    */
        if ((src_coordinates.row >= this->board.height() or src_coordinates.col >= this->board.width())
            or (dst_coordinates.row >= this->board.height() or dst_coordinates.col >= this->board.width())
            or (src_coordinates.row < 0 or src_coordinates.col < 0)
            or (dst_coordinates.row < 0 or dst_coordinates.col < 0)){
                throw IllegalCell();
            }
        else if(this->board(src_coordinates.row, src_coordinates.col) == nullptr){
            throw CellEmpty();
        }
    this->board(src_coordinates.row, src_coordinates.col)->attack(this->board, src_coordinates, dst_coordinates);
}

void Game::reload(const GridPoint & coordinates){
    /*
    Throw Exceptions:
        1. GameException::IllegalCell if coordinates are out of grid.
        2. GameException::CellEmpty if in src_coordinates is no charecter to reload.
    */
    if ((coordinates.row >= this->board.height() or coordinates.col >= this->board.width())
        or (coordinates.row < 0 or coordinates.col < 0)){
            throw IllegalCell();
        }
        else if(this->board(coordinates.row, coordinates.col) == nullptr){
            throw CellEmpty();
        }
    this->board(coordinates.row, coordinates.col)->reload();
}

std::ostream& operator<<(std::ostream& os, const Game& game){
    // Build char* from game.board
    std::string str_repr = std::string();
    std::string default_char = std::string(" ");

    for(int row=0;row < game.board.height();++row){
        for(int col=0;col < game.board.width();++col){
            std::string str_cell = default_char;
            if(game.board(row,col) != nullptr){
                str_cell = game.board(row,col)->to_str();
            }
            str_repr.append(str_cell);
        }
    }
    const char* begin = str_repr.c_str();
    const char* end = str_repr.c_str() + str_repr.size();
    return printGameBoard(os, begin, end, game.board.width());
}

bool Game::isOver(Team* winningTeam) const{
    int python_counter=0;
    int cpp_counter=0;
    bool is_over = false;
    for(int row=0; row<board.height();++row){
        for (int col=0; col<board.width(); ++col){
            if (board(row,col) != nullptr){
                if (board(row,col)->get_team() == PYTHON){
                    python_counter++;
                }
                else{
                    cpp_counter++;
                }
            }
        }
    }
    if ((python_counter > 0 and cpp_counter == 0) or 
        (python_counter == 0 and cpp_counter > 0)){
            is_over = true;
        }


    if (winningTeam != NULL){
        if((python_counter > 0) and (cpp_counter==0)){
        *winningTeam = PYTHON;
        }
    else if ((cpp_counter > 0) and (python_counter ==0)){
        *winningTeam = CPP;
        }
    
    }
    return is_over;
    }

}

