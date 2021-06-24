#include "Board.h"
#include "Character.h"
#include "Exceptions.h"
using namespace mtm;

Board::Board(int height, int width): height(height), width(width){
    if (height<=0 || width<= 0){
        throw IllegalArgument();
    }
    board=std::vector<std::shared_ptr<Character>>(height*width, nullptr);
}

std::shared_ptr<Character> Board::operator()(int row, int col) {
    if (row<0 || col<0 || row > this->height || col>this->width){
        throw IllegalCell();
    }
    int cell = this->width * row + col;
    return this->board.at(cell);
}

int Board::getHeight() {
    return this->height;
}

int Board::getWidth() {
    return this->width;
}

std::vector<std::shared_ptr<Character>> Board::getBoard() {
    return this->board;
}
