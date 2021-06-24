#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <memory>
#include <list>
#include "Auxiliaries.h"
#include "Character.h"


namespace mtm{
    class Game{
        std::vector<std::shared_ptr<Character>> board;

        /**
             * //bool isCellLegal(const GridPoint& coordinates)//:
             * receives a GridPoint named coordinates
             * returns true if coordinates form a legal cell in game's Board (not outside the Board, not negative)
             * returns false otherwise
        */
        bool isCellLegal(const GridPoint& coordinates);
        
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
        
        /**
            * //int getSize() const//:
            * returns the size of the game's Board
        */
        int getSize() const;
        
        /**
            * //int getHeight() const//:
            * returns the height of the game's Board
        */
        int getHeight() const;
        
        /**
            * //int getWidth() const//:
            * returns the width of the game's Board
        */
        int getWidth() const;
        
        /**
             * //static Matrix<std::shared_ptr<Character>> copyBoard(const Game& game)//:
             * receives a reference to game
             * returns a copy of the Board's game to this Board
        */
        static std::vector<std::shared_ptr<Character>> copyBoard(const Game& game);
        
        /**
             * //std::shared_ptr<Character>& operator()(int row, int col)//:
             * receives two ints' representing number of rows and number of columns
             * 
        */
        std::shared_ptr<Character>& operator()(int row, int col);
        
        /**
             * //std::shared_ptr<Character>& operator()(const GridPoint& gp)//:
             * receives a reference to GridPoint named gp
             * returns the smart pointer in cell with coordinates gp of the game's Board
        */
        std::shared_ptr<Character>& operator()(const GridPoint& gp);
        
        /**
             * //const std::shared_ptr<Character>& operator()(int row, int col) const//:
             * receives a reference to GridPoint named gp
             * returns the constant smart pointer in cell with coordinates gp of the game's Board
        */
        const std::shared_ptr<Character>& operator()(int row, int col) const;
    
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
        ~Game();
        /**
             * //Game(const Game& other)//:
             * - Game copy constructor
             * receives a param Game named other
        */
        Game(const Game& other);

        /**
             * //Game& operator=(const Game& other)//:
             * - Game's assignment operator
             * receives a param Game named other
             * makes this' Board identical to the Board of other
        */
        Game& operator=(const Game& other);

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