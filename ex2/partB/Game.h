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
             * //void clearDead()//:
             * checks all Board's characters health
             * If a character's health is zero, the character is removed from the Board
        */
        void clearDead();
        
        /**
             * //void fillSecondaryTargetsList(const GridPoint src_coordinates, const GridPoint dst_coordinates,
               std::list<std::shared_ptr<Character>>& secondary_targets)//:
             * receives two GridPoints and a list of shared_pointers to Character
             * the list is filled with shared pointers to characters in range of damage from a Soldier's attack
        */
        void fillSecondaryTargetsList(GridPoint src_coordinates, GridPoint dst_coordinates,
        std::list<std::shared_ptr<Character>>& secondary_targets);
    
    public:
        /**
             * //Game(int height, int width)//:
             * Game constructor.
             * receives dimensions of Game's Board.
             * constructs Matrix<T> , each element set to initial_value.
        */
        Game(int height, int width);

        /**
             * //~Game()//: 
             * a game destructor
             *  destroys game 
        */ 
        ~Game()=default;
        /**
             * //Game(const Game& other)//:
             * - Game copy constructor
             * receives a param Game named other
        */
        Game(const Game& other)=default;

        /**
             * //Game& operator=(const Game& other)//:
             * - Game's assignment operator
             * receives a param Game named other
             * makes this' Board identical to the Board of other
        */
        Game& operator=(const Game& other)=default;

        /**
             * //void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)//:
             * receives params GridPoint named coordinates and shared pointer to Character named character
             * adds character to the game's Board in point coordinates
        */
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        
        /** 
             * //static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health,
                units_t ammo, units_t range, units_t power)//:
             * receives all params required to create a Character and it's type
             *returns a shared pointer to the new Character
        */  
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health,
            units_t ammo, units_t range, units_t power);
        
        /** 
            *  //void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)//
            *  receives two GridPoints
            *  moves the character currently in src_coordinates, to dst_coordinates
        */
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        
        /** 
            * //void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)//:
            * receives two GridPoints
            * attacks the character currently in dst_coordinates with the character in src_coordinates
        */
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        
        /** 
            * //void reload(const GridPoint & coordinates)//:
            * receives a GridPoint named coordinates
            * reloads the ammo of the character at the given coordinates
        */
        void reload(const GridPoint & coordinates);
        
        /** 
             * //isOver(Team* winningTeam=NULL) const//:
             * receives a pointer to a Team 
             * checks if the games is over according to the rules.
             * returns true if the game is over. false, otherwise. 
        */
        bool isOver(Team* winningTeam=nullptr) const;
         
        /** 
             * //std::ostream& operator<<(std::ostream &os, const Game& game)//:
             * receives ostream os and a game 
             * prints the given game
        */
        friend std::ostream& operator<<(std::ostream &os, const Game& game);
    };

    //a friend operator which was declared in Game class
    std::ostream& operator<<(std::ostream &os, const Game& game);
}

#endif // GAME_H