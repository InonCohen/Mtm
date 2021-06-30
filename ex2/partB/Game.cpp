#include <memory>
#include <list>
#include "Game.h"
#include "Board.h"
#include "Character.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "Exceptions.h"
#include "Auxiliaries.h"


namespace mtm{
    static const char EMPTY_CELL=' ';
    static const char CPP_SOLDIER='S';
    static const char PYTHON_SOLDIER='s';
    static const char CPP_MEDIC='M';
    static const char PYTHON_MEDIC='m';
    static const char CPP_SNIPER='N';
    static const char PYTHON_SNIPER='n';

    /**
     * characterRepresentation: Match a unique char to character type from a given team.
     * @param Ptr to character
     * @return appropriate char, considering Team and CharacterType.
     */
    static char characterRepresentation(const std::shared_ptr<Character>& character);

    Game::Game(int height, int width): gameBoard(Board<Character>(height, width)) {}

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health,
                                                   units_t ammo, units_t range, units_t power){
        if(health<=0||ammo<0||range<0||power<0){
            throw IllegalArgument();
        }
        if(type == SOLDIER) {
            return std::make_shared<Soldier>(Soldier(team, health, ammo, range, power));
        }
        else if (type==MEDIC) {
            return std::make_shared<Medic>(Medic(team, health, ammo, range, power));
        }
        return std::make_shared<Sniper>(Sniper(team, health, ammo, range, power));
    }

    void Game::addCharacter(const GridPoint& gp, std::shared_ptr<Character> character_ptr){
        this->gameBoard.addItem(gp, character_ptr);
    }

    std::ostream& operator<<(std::ostream &os, const mtm::Game& game) {
        int gameBoardHeight = game.gameBoard.getHeight();
        int gameBoardWidth = game.gameBoard.getWidth();
        int gameBoardSize = gameBoardHeight * gameBoardWidth;
        char* char_board = new char[gameBoardSize];
        int count=0;
        for (int i=0;i<gameBoardHeight;i++){
            for (int j=0;j<gameBoardWidth;j++){
                const GridPoint gp(i,j);
                char_board[count++]= characterRepresentation(game.gameBoard(gp));
            }
        }

        std::ostream& print=printGameBoard(os, &char_board[0], &char_board[gameBoardSize], game.gameBoard.getWidth());
        delete[] char_board;
        return print;
    }


    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
        if(!(this->gameBoard.isCellLegal(src_coordinates) && this->gameBoard.isCellLegal(dst_coordinates))){
            throw IllegalCell();
        }
        if(!this->gameBoard(src_coordinates)){
            throw CellEmpty();
        }
        std::shared_ptr<Character> to_move_ptr=this->gameBoard(src_coordinates);
        if (!((*to_move_ptr).isMoveLegal(GridPoint::distance(src_coordinates,dst_coordinates)))){
            throw MoveTooFar();
        }
        this->gameBoard.moveItem(src_coordinates, dst_coordinates);
    }


    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
        if(!(this->gameBoard.isCellLegal(src_coordinates) && this->gameBoard.isCellLegal(dst_coordinates))){
            throw IllegalCell();
        }
        if(!this->gameBoard(src_coordinates)){
            throw CellEmpty();
        }
        std::shared_ptr<Character> attacker_ptr=this->gameBoard(src_coordinates);
        if(!((attacker_ptr.get())->isAttackLegal(src_coordinates, dst_coordinates))){
            throw OutOfRange();
        }
        std::shared_ptr<Character> target_ptr=this->gameBoard(dst_coordinates);
        if (!((attacker_ptr.get())->isAmmoSufficient(target_ptr))){
            throw OutOfAmmo();
        }
        if(!((attacker_ptr.get())->isTargetLegal(target_ptr))||
        !(attacker_ptr->isTargetPositionLegal(src_coordinates,dst_coordinates))){
            throw IllegalTarget();
        }
        (attacker_ptr.get())->attack(target_ptr);
        if((attacker_ptr.get())->getType()==SOLDIER) {
            std::list<std::shared_ptr<Character>> secondary_targets;
            fillSecondaryTargetsList(src_coordinates, dst_coordinates, secondary_targets);
            (attacker_ptr.get())->attack(secondary_targets);
        }
        clearDead();
    }

    void Game::reload(const GridPoint& coordinates){
        if(!this->gameBoard.isCellLegal(coordinates)){
            throw IllegalCell();
        }
        std::shared_ptr<Character> character= this->gameBoard(coordinates);
        if(character == nullptr){
            throw CellEmpty();
        }
        (*character).reload();
    }

    void Game::clearDead() {
        for(int i=0; i < gameBoard.getHeight(); i++){
            for(int j=0; j < gameBoard.getWidth(); j++){
                const GridPoint gp(i,j);
                Character* current_character_ptr = gameBoard(gp).get();
                if(gameBoard(gp) != nullptr && !(current_character_ptr->isAlive())){
                    gameBoard.removeItem(gp);
                }
            }
        }
    }

     void Game::fillSecondaryTargetsList(const GridPoint src_coordinates, const GridPoint dst_coordinates,
            std::list<std::shared_ptr<Character>>& secondary_targets){
        Character& attacker= *(this->gameBoard(src_coordinates));
        for(int i=0; i < this->gameBoard.getHeight(); i++) {
            for (int j = 0; j < this->gameBoard.getWidth(); j++) {
                const GridPoint gp(i,j);
                if(this->gameBoard(gp) != nullptr && attacker.isSecondaryTarget(dst_coordinates, gp) &&
                (*(this->gameBoard(gp))).getTeam()!=attacker.getTeam()){
                    secondary_targets.push_back(this->gameBoard(gp));
                }
            }
        }
    }

    bool Game::isOver(Team* winningTeam) const{
        int countCPP=0, countPython=0;
        for(int i=0; i < gameBoard.getHeight(); i++) {
            for (int j = 0; j < gameBoard.getWidth(); j++) {
                const GridPoint gp(i,j);
                if (gameBoard(gp) != nullptr && (gameBoard(gp).get())->getTeam() == POWERLIFTERS) {
                    countCPP++;
                } else if (gameBoard(gp) != nullptr && (gameBoard(gp).get())->getTeam() == CROSSFITTERS) {
                    countPython++;
                }
            }
        }
        if((countCPP!=0&&countPython!=0)||(countCPP==0&&countPython==0)){
            return false;
        }
        if (winningTeam!= nullptr){
            if(countCPP==0) {
                *winningTeam = CROSSFITTERS;
            }
            else{
                *winningTeam = POWERLIFTERS;
            }
        }
        return true;
    }

    static char characterRepresentation(const std::shared_ptr<Character>& character) {
        if (character == nullptr) {
            return EMPTY_CELL;
        }
        if ((character.get())->getTeam() == POWERLIFTERS) {
            if ((character.get())->getType() == SOLDIER) {
                return CPP_SOLDIER;
            }
            if ((character.get())->getType() == MEDIC) {
                return CPP_MEDIC;
            }
            return CPP_SNIPER;
        }
        else
        {
            if ((character.get())->getType() == SOLDIER) {
                return PYTHON_SOLDIER;
            }
            if ((character.get())->getType() == MEDIC) {
                return PYTHON_MEDIC;
            }
            return PYTHON_SNIPER;
        }
    }
}