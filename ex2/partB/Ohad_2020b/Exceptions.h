#ifndef HW3_EXCEPTION_H
#define HW3_EXCEPTION_H
#include <exception>
#include <iostream>       // std::cerr

namespace mtm{
    class Exception : public std::exception{
        public:
            Exception() = default;
            virtual ~Exception() = default;
            virtual const char* what() const noexcept{
                return "";
            }
    };

    class GameException : public Exception{
        public:
            GameException() = default;
            virtual ~GameException() = default;
            virtual const char* what() const noexcept{
                return "A game related error has occurred: ";
            }
        };

    class IllegalArgument : public GameException{
        std::string game_str = GameException::what() + std::string("IllegalArgument");
        public:
            IllegalArgument() = default;
            ~IllegalArgument() = default;
            virtual const char* what() const noexcept{
                return game_str.c_str();
            }
    };
    
    class IllegalCell : public GameException{
        std::string game_str = GameException::what() + std::string("IllegalCell");

        public:
            IllegalCell() = default;
            ~IllegalCell() = default;
            virtual const char* what() const noexcept{
                return game_str.c_str();
            }

    };
    
    class CellEmpty : public GameException{
        std::string game_str = GameException::what() + std::string("CellEmpty");
        public:
            CellEmpty() = default;
            ~CellEmpty() = default;
            virtual const char* what() const noexcept{
                return game_str.c_str();
            }


    };
    
    class MoveTooFar : public GameException{
        std::string game_str = GameException::what() + std::string("MoveTooFar");
        public:
            MoveTooFar() = default;
            ~MoveTooFar() = default;
            virtual const char* what() const noexcept{
                return game_str.c_str();
            }
    };

    class CellOccupied : public GameException{
        std::string game_str = GameException::what() + std::string("CellOccupied");

        public:
            CellOccupied() = default;
            ~CellOccupied() = default;
            virtual const char* what() const noexcept{
                return game_str.c_str();
            }
    };
   
    class OutOfRange : public GameException{
        std::string game_str = GameException::what() + std::string("OutOfRange");
        public:
            OutOfRange() = default;
            ~OutOfRange() = default;
            virtual const char* what() const noexcept{
                return game_str.c_str();
            }
    };

    class OutOfAmmo : public GameException{
        std::string game_str = GameException::what() + std::string("OutOfAmmo");
         
        public:
            OutOfAmmo() = default;
            ~OutOfAmmo() = default;
            virtual const char* what() const noexcept{
                return game_str.c_str();
            }
   };

    class IllegalTarget : public GameException{
        std::string game_str = GameException::what() + std::string("IllegalTarget");
        public:
            IllegalTarget() = default;
            ~IllegalTarget() = default;
            virtual const char* what() const noexcept{
                return game_str.c_str();
                }
   };
}
#endif