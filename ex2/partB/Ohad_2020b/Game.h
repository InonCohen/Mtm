#include "Auxiliaries.h"
#include "Matrix.h"
#include "Character.h"
#include "Sniper.h"
#include "Soldier.h"
#include "Medic.h"
#include "Exceptions.h"
#include <memory>
#include <iostream>
/*
In order to enable multiple games of the same character, I have decided a character doesn't aware to its own location on the game board.
So in order to act (move ar attack) game should manage the operation.
*/
namespace mtm{
    class Game{        
        private:
        Matrix<std::shared_ptr<Character>> board = Matrix<std::shared_ptr<Character>> (Dimensions(1,1));

        public:
            Game(int height, int width);
            ~Game() = default;
            Game(const Game& other) = default;
            Game& operator=(const Game& other);
            
            static std::shared_ptr<Character> makeCharacter(CharacterType type,
             Team team, units_t health, units_t ammo, units_t range, units_t power);
            void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
            
            void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            void reload(const GridPoint & coordination);
           
            friend std::ostream& operator<<(std::ostream& os, const Game&);
            bool isOver(Team* winningTeam=NULL) const;

    };
}
