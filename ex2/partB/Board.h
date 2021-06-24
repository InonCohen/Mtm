#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include "Character.h"

namespace mtm {
    class Board {
        int height;
        int width;
        std::vector<std::shared_ptr<Character>> board;
    public:
        Board(int height, int width);
        int getHeight();
        int getWidth();
        std::vector<std::shared_ptr<Character>> getBoard();
        std::shared_ptr<Character> operator()(int row, int col);
    };
}

#endif //BOARD_H
