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

    class GameException : public Exception {
        const char* error_name;
    protected:
        const char full_error [ERROR_LENGTH] = {0};
    public:
        explicit GameException(const char* error_name);
        ~GameException()=default;
        const char* what() const noexcept override;
    };

    class IllegalArgument: public GameException {
    public:
        IllegalArgument();
        ~IllegalArgument()=default;
    };

    class IllegalCell: public GameException {
    public:
        IllegalCell();
        ~IllegalCell()=default;
    };

    class CellEmpty: public GameException {
    public:
        CellEmpty();
        ~CellEmpty()=default;
    };

    class MoveTooFar:public GameException {
    public:
        MoveTooFar();
        ~MoveTooFar()=default;
    };

    class CellOccupied:public GameException {
    public:
        CellOccupied();
        ~CellOccupied()=default;
    };

    class OutOfRange:public GameException {
    public:
        OutOfRange();
        ~OutOfRange()=default;
    };

    class OutOfAmmo:public GameException {
    public:
        OutOfAmmo();
        ~OutOfAmmo()=default;
    };

    class IllegalTarget:public GameException {
    public:
        IllegalTarget();
        ~IllegalTarget()=default;
    };

}

#endif //EXCEPTIONS_H
