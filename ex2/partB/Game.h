#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <memory>
#include <list>
#include "Auxiliaries.h"
#include "Character.h"
#include "Board.h"


namespace mtm{
    class Game{
        Board<Character> gameBoard;
        /**
         * clearDead: Checks all character's health on the board.
         * Character is being removed from the Board if its health is zero.
         */
        void clearDead();
        
        /**
         * fillSecondaryTargetsList: Called when a soldier character is attacking.
         * Builds secondary_target list - shared pointers to characters in the range of damage from a Soldier's attack.
         * @param src_coordinates: Soldier's coordination
         * @param dst_coordinates: Target's coordination
         * @param secondary_targets: Pointer to secondary_targets list
         */
        void fillSecondaryTargetsList(GridPoint src_coordinates, GridPoint dst_coordinates,
        std::list<std::shared_ptr<Character>>& secondary_targets);
    
    public:
        /**
         * Game Constructor. Receives dimensions of Game's Board,
         * constructs Board<std::shared_ptr<Character>> data structure.
         * @param height: Height of game board.
         * @param width: Width of game board.
         *
         * @throw IllegalArgument:
         */
        Game(int height, int width);

        /**
         * Game Destructor.
         */
        ~Game()=default;

        /**
         * Game Copy Constructor.
         * @param other: Game& to copy
         */
        Game(const Game& other)=default;

        /**
         * Game Assignment Operator.
         * receives a param Game named other
         * makes this' Board identical to the Board of other
         * @param other
         * @return Game& of the assigned game.
         */
        Game& operator=(const Game& other)=default;

        /**
         * addCharacter: Adds character to the game's Board in a given gridpoint
         * @param coordinates: GridPoint on game board to add the character into.
         * @param character: Ptr to Character object to-be added
         *
         * @throw IllegalCell
         * @throw CellOccupied
         */
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        
        /** 
         * makeCharacter: Creates a character from the following params
         * @param type: One of the following: Medic, Sniper, Soldier
         * @param team: One of Team enum teams
         * @param health: Initial health units of the character. Positive integer.
         * @param ammo: Initial ammunition of the character.
         * @param range: attack range of the character.
         * @param power: Power attack of the character.
         *
         * @throw IllegalArgument:
         * @return Shared ptr to the new Character
         */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health,
            units_t ammo, units_t range, units_t power);
        
        /** 
         * move: Moves character currently in src_coordinates to dst_coordinates.
         *
         * @param src_coordinates: GridPoint character is currently in.
         * @param dst_coordinates: GridPoint to move character into
         *
         * @throw IllegalCell: coordinates aren't in gameBoard.
         * @throw CellEmpty: src_coordinates is empty or dst_coordinates isn't empty.
         * @throw MoveTooFar: defined max range of move for character of the given type isn't enough
         */
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        
        /** 
         * attack: Apply attack of a character on a destination on board.
         *
         * @param src_coordinates: GridPoint of the attacking character
         * @param dst_coordinates:
         *
         * @throw IllegalCell:
         * @throw CellEmpty:
         * @throw OutOfRange:
         * @throw OutOfAmmo:
         * @throw IllegalTarget:
         */
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        
        /** 
         * //void reload(const GridPoint & coordinates)//:
         * receives a GridPoint named coordinates
         * reloads the ammo of the character at the given coordinates
         *
         * @param coordinates
         *
         * @throw IllegalCell:
         * @throw CellEmpty:
         */
        void reload(const GridPoint & coordinates);
        
        /** 
         * //isOver(Team* winningTeam=NULL) const//:
         * receives a pointer to a Team
         * checks if the games is over according to the rules.
         * returns true if the game is over. false, otherwise.
         *
         * @param winningTeam
         * @return
         */
        bool isOver(Team* winningTeam=nullptr) const;
         
        /** 
         * //std::ostream& operator<<(std::ostream &os, const Game& game)//:
         * receives ostream os and a game
         * prints the given game
         *
         * @param os
         * @param game
         * @return
         */
        friend std::ostream& operator<<(std::ostream &os, const Game& game);
    };

    //a friend operator which was declared in Game class
    std::ostream& operator<<(std::ostream &os, const Game& game);
}

#endif // GAME_H