#include "Exceptions.h"
#include <cstring>
#define ILLEGAL_ARGUMENT "IllegalArgument"
#define ILLEGAL_CELL "IllegalCell"
#define CELL_EMPTY "CellEmpty"
#define MOVE_TOO_FAR "MoveTooFar"
#define CELL_OCCUPIED "CellOccupied"
#define OUT_OF_RANGE "OutOfRange"
#define OUT_OF_AMMO "OutOfAmmo"
#define ILLEGAL_TARGET "IllegalTarget"

namespace mtm{
    GameException::GameException(const char* error_name):error_name(error_name){}

    IllegalArgument::IllegalArgument():GameException(ILLEGAL_ARGUMENT){}

    IllegalCell::IllegalCell():GameException(ILLEGAL_CELL){}

    CellEmpty::CellEmpty():GameException(CELL_EMPTY){}

    MoveTooFar::MoveTooFar():GameException(MOVE_TOO_FAR){}

    CellOccupied::CellOccupied():GameException(CELL_OCCUPIED){}

    OutOfRange::OutOfRange():GameException(OUT_OF_RANGE){}

    OutOfAmmo::OutOfAmmo():GameException(OUT_OF_AMMO){}

    IllegalTarget::IllegalTarget(): GameException(ILLEGAL_TARGET){}

    const char* GameException::what() const noexcept{
        strcpy(const_cast<char *>(full_error), game_error_str);
        strcat(const_cast<char *>(full_error), error_name);
        return const_cast<char *>(full_error);
    }
}
