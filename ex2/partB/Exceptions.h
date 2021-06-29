#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <string>


namespace mtm {


    static const int ERROR_LENGTH=100;

    class Exception: public std::exception {
    protected:
        const char* game_error_str="A game related error has occurred: ";

    public:
        virtual const char* what() const noexcept=0;
    };

    /**
     * A class from which all possibly-thrown exceptions inherit.
     */
    class GameException : public Exception {
        const char* error_name;
    protected:
        const char full_error [ERROR_LENGTH] = {0};
    public:
        explicit GameException(const char* error_name);
        ~GameException()=default;
        const char* what() const noexcept override;
    };

    //Declaration of all the exceptions that might be thrown while playing a Game//

    /**
     * An exception that is thrown when the user is trying to use an illegal parameter.
     */
    class IllegalArgument: public GameException {
    public:
        IllegalArgument();
        ~IllegalArgument()=default;
    };

    /**
     * An exception that is thrown when a target cell is outside the game's board.
     */
    class IllegalCell: public GameException {
    public:
        IllegalCell();
        ~IllegalCell()=default;
    };

    /**
     * An exception that is thrown when a source cell is empty, or when a target cell
     * is empty under circumstances that don't allow it.
     */
    class CellEmpty: public GameException {
    public:
        CellEmpty();
        ~CellEmpty()=default;
    };

    /**
     * An exception that is thrown when the user is trying to move a Character
     * farther than its moving range allows
     */
    class MoveTooFar:public GameException {
    public:
        MoveTooFar();
        ~MoveTooFar()=default;
    };

    /**
     * An exception that is thrown when the user is trying to put a Character
     * in a cell that already contains a Character
     */
    class CellOccupied:public GameException {
    public:
        CellOccupied();
        ~CellOccupied()=default;
    };

    /**
     * An exception that is thrown when a Character is trying to attack a cell
     * that is farther than its attack range allows
     */
    class OutOfRange:public GameException {
    public:
        OutOfRange();
        ~OutOfRange()=default;
    };

    /**
     * An exception that is thrown when a Character is trying to attack, but
     * doesn't have enough ammunition for it
     */
    class OutOfAmmo:public GameException {
    public:
        OutOfAmmo();
        ~OutOfAmmo()=default;
    };

    /**
     * An exception that is thrown when a Character is trying to attack a cell
     * that it isn't allowed to attack, for reasons that differ from range or lack
     * of ammunition
     */
    class IllegalTarget:public GameException {
    public:
        IllegalTarget();
        ~IllegalTarget()=default;
    };

}

#endif //EXCEPTIONS_H
