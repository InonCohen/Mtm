#include "Game.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "Matrix.h"
#include "Exceptions.h"
#include <iostream>
#include "Auxiliaries.h"
#include <memory>
#include <list>


namespace mtm{
    static const char EMPTY_CELL=' ';
    static const char CPP_SOLDIER='S';
    static const char PYTHON_SOLDIER='s';
    static const char CPP_MEDIC='M';
    static const char PYTHON_MEDIC='m';
    static const char CPP_SNIPER='N';
    static const char PYTHON_SNIPER='n';

    /**
     * //static char getLetter(const std::shared_ptr<Character>& character)//:
     * receives a shared pointer to Character named character
     * returns the letter symbolizes the character on the board
*/
    static char getLetter(const std::shared_ptr<Character>& character);

    Game::Game(int height, int width): board((height<=0 || width<= 0) ? throw IllegalArgument() : Matrix<std::shared_ptr<Character>>(Dimensions(height,width),nullptr)){}

    Game::~Game(){
        int height=this->getHeight();
        int width=this->getWidth();
        for(int i=0;i<height;i++){
            for (int j=0;j<width;j++){
                board(i,j) = nullptr;
            }
        }
    }

    Game::Game(const mtm::Game& other): board(copyBoard(other)){
    }

    int Game::getSize() const{
        return this->board.size();
    }

    int Game::getHeight() const{
        return this->board.height();
    }

    int Game::getWidth() const{
        return this->board.width();
    }

    const std::shared_ptr<Character>& Game::operator()(int row, int col) const{
        if (row<0||col<0||row>this->getHeight()||col>this->getWidth()){
            throw IllegalCell();
        }
        return board(row,col);
    }

    std::shared_ptr<Character>& Game::operator()(int row, int col){
        if (row<0||col<0||row>this->getHeight()||col>this->getWidth()){
            throw IllegalCell();
        }
        return board(row,col);
    }

    std::shared_ptr<Character>& Game::operator()(const GridPoint& gp){
        int row=gp.row;
        int col=gp.col;
        return this->operator()(row,col);
    }

    Game& Game::operator=(const Game& other){
        this->board = copyBoard(other);
        return *this;
    }

    Matrix<std::shared_ptr<Character>> Game::copyBoard(const Game& game) {
        auto board = Matrix<std::shared_ptr<Character>>(Dimensions(game.board.height(), game.board.width()), nullptr);
        int height = game.board.height();
        int width = game.board.width();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (game.board(i, j)) {
                    board(i, j) = std::shared_ptr<Character>(game.board(i, j)->clone());
                }
            }
        }
        return board;
    }

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

    bool Game::isCellLegal(const GridPoint& coordinates){
        int row=coordinates.row;
        int col=coordinates.col;
        if(row<0||row>=this->getHeight()||col<0||col>=this->getWidth())
            return false;
        return true;
    }

    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character){
        if (!isCellLegal(coordinates)){
            throw IllegalCell();
        }
        if(this->operator()(coordinates)!=NULL){
            throw CellOccupied();
        }
        this->operator()(coordinates)=character;
    }

    static char getLetter(const std::shared_ptr<Character>& character){
        if(character==nullptr){
            return EMPTY_CELL;
        }
        if((character.get())->getTeam()==CPP){
            if((character.get())->getType()==SOLDIER){
                return CPP_SOLDIER;
            }
            if((character.get())->getType()==MEDIC){
                return CPP_MEDIC;
            }
            return CPP_SNIPER;
        }
        if((character.get())->getType()==SOLDIER){
            return PYTHON_SOLDIER;
        }
        if((character.get())->getType()==MEDIC){
            return PYTHON_MEDIC;
        }
        return PYTHON_SNIPER;
    }

    std::ostream& operator<<(std::ostream &os, const mtm::Game& game) {
        int size = game.getSize();
        int height = game.getHeight();
        int width = game.getWidth();
        char* char_board = new char[size];
        int count=0;
        for (int i=0;i<height;i++){
            for (int j=0;j<width;j++){
                char_board[count++]=getLetter(game(i,j));
            }
        }
        std::ostream& print=printGameBoard(os, &char_board[0], &char_board[size], game.getWidth());
        delete[] char_board;
        return print;
    }

    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
        if(!isCellLegal(src_coordinates)||!isCellLegal(dst_coordinates)){
            throw IllegalCell();
        }
        std::shared_ptr<Character> to_move_ptr=this->operator()(src_coordinates);
        if(to_move_ptr== nullptr){
            throw CellEmpty();
        }
        if (!((*to_move_ptr).isMoveLegal(GridPoint::distance(src_coordinates,dst_coordinates)))){
            throw MoveTooFar();
        }
        if(!(this->operator()(dst_coordinates)==nullptr)){
            throw CellOccupied();
        }
        auto temp = this->operator()(src_coordinates);
        this->operator()(src_coordinates) = nullptr;
        this->operator()(dst_coordinates)=temp;
    }

    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
        if(!isCellLegal(src_coordinates)||!isCellLegal(dst_coordinates)){
            throw IllegalCell();
        }
        std::shared_ptr<Character> attacker_ptr=this->operator()(src_coordinates);
        if(attacker_ptr == nullptr){
            throw CellEmpty();
        }
        if(!((attacker_ptr.get())->isAttackLegal(src_coordinates, dst_coordinates))){
            throw OutOfRange();
        }
        std::shared_ptr<Character> target_ptr=this->operator()(dst_coordinates);
        if (!((attacker_ptr.get())->isAmmoSufficient(target_ptr))){
            throw OutOfAmmo();
        }
        if(!((attacker_ptr.get())->isTargetLegal(target_ptr))||
        !(attacker_ptr.get()->isTargetPositionLegal(src_coordinates,dst_coordinates))){
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
        if(!isCellLegal(coordinates)){
            throw IllegalCell();
        }
        std::shared_ptr<Character> character= this->operator()(coordinates);
        if(character == nullptr){
            throw CellEmpty();
        }
        (*character).reload();
    }

    void Game::clearDead() {
        for(int i=0;i<board.height();i++){
            for(int j=0;j<board.width();j++){
                if(board(i,j)!= nullptr && !((*(board(i,j))).isAlive())){
                    board(i,j)=nullptr;
                }
            }
        }
    }

    void Game::fillSecondaryTargetsList(const GridPoint src_coordinates, const GridPoint dst_coordinates,
            std::list<std::shared_ptr<Character>>& secondary_targets){
        Character& attacker= *(this->operator()(src_coordinates));
        for(int i=0;i<board.height();i++) {
            for (int j = 0; j < board.width(); j++) {
                if(board(i,j)!=nullptr&& attacker.isSecondaryTarget(dst_coordinates, GridPoint(i,j)) &&
                (*(this->operator()(GridPoint(i,j)))).getTeam()!=attacker.getTeam()){
                    secondary_targets.push_back(board(i,j));
                }
            }
        }
    }

    bool Game::isOver(Team* winningTeam) const{
        int countCPP=0, countPython=0;
        for(int i=0;i< board.height();i++) {
            for (int j = 0; j < board.width(); j++) {
                if (board(i, j) != nullptr && (board(i, j).get())->getTeam() == CPP) {
                    countCPP++;
                } else if (board(i, j) != nullptr && (board(i, j).get())->getTeam() == PYTHON) {
                    countPython++;
                }
            }
        }
        if((countCPP!=0&&countPython!=0)||(countCPP==0&&countPython==0)){
            return false;
        }
        if (winningTeam!= nullptr){
            if(countCPP==0) {
                *winningTeam = PYTHON;
            }
            else{
                *winningTeam = CPP;
            }
        }
        return true;
    }
}