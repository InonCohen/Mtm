#ifndef EX2_BOARD_H
#define EX2_BOARD_H
#include <vector>
#include <memory>
#include "Exceptions.h"


namespace mtm {
    template <class T>
    class Board{
        int height;
        int width;
        std::vector<std::shared_ptr<T>> board;
    public:
        /**
         * Board Constructor.
         *
         * @param height: Height of board
         * @param width: Width of board
         *
         * @throw IllegalArgument: given height or width aren't positive integers
         */
        Board(int height, int width);

        /**
         * Board Copy Constructor.
         *
         * Template Requirements:
         * - clone()
         * - copy constructor (derived from clone)
         *
         * @param other: const Board reference
         */
        Board(const Board& other);

        /**
         * Board Destructor.
         *
         */
        ~Board();

        /**
         * Board Assignment Operator.
         *
         * Template Requirements:
         * - clone()
         * - copy constructor (derived from clone)
         *
         * @param other: Board to assign to
         * @return
         */
        Board& operator=(const Board& other);

        /**
         * Board Parentheses Operator. Functions as index operator - given a GridPoint, applies translation to
         * board coordinates.
         *
         * @param gp: GridPoint on board to access
         * @return Ptr to the requested GridPoint on board.
         */
        std::shared_ptr<T>& operator()(const GridPoint& gp);

        /**
         * Board const Parentheses Operator. Functions as index operator - given a GridPoint, applies translation to
         * board coordinates.
         *
         * @param gp: GridPoint on board to access
         * @return Ptr to the requested GridPoint on board.
         */
        const std::shared_ptr<T>& operator()(const GridPoint& gp) const;

        /**
         * getHeight: Get height of board.
         *
         * @return Height of board.
         */
        int getHeight() const;

        /**
         * getWidth: Get width of board.
         *
         * @return Width of board.
         */
        int getWidth() const;

        /**
         * getBoardSize: Get size of board.
         *
         * @return Size of the board (num GridPoints in board)
         */
        int getBoardSize() const;

        /**
         * addItem: Add an item to board.
         *
         * @param gp: GridPoint to add item in
         * @param item: item to add to the board
         *
         * @throw IllegalCell: gp isn't in board
         * @throw CellOccupied: cell isn't empty
         */
        void addItem(const GridPoint& gp, std::shared_ptr<T> item);

        /**
         * removeItem: Remove an item from board. Set GridPoint to null pointer instead.
         *
         * Template Requirements:
         * - Destructor
         *
         * @param gp: GridPoint to remove item from.
         */
        void removeItem(const GridPoint& gp);

        /**
         * moveItem: Move an item on board.
         *
         * @param src_gp: move item from
         * @param dst_gp: move item into
         * @throw IllegalCell: given GridPoints aren't in board
         * @throw CellEmpty: there is no item in the source GridPoint
         * @throw CellOccupied: there is already an item in the destination GridPoint
         */
        void moveItem(const GridPoint& src_gp, const GridPoint& dst_gp);

        /**
         * isCellLegal: Check if a GridPoint is legal, means that it's inside board.
         *
         * @param gp: GridPoint to test validity
         * @return true if cell is legal, false otherwise.
         */
        bool isCellLegal(const GridPoint& gp);
    };

    // Implementation of `Board` methods
    template <class T>
    Board<T>::Board(int height, int width):
            height(height<=0 ? throw IllegalArgument() : height),
            width(width<=0 ? throw IllegalArgument() : width),
            board(std::vector<std::shared_ptr<T>>(this->getBoardSize(), nullptr))
    {}

    template<class T>
    Board<T>::Board(const Board & other):
            height(other.height),
            width(other.width),
            board(std::vector<std::shared_ptr<T>>(this->getBoardSize(), nullptr)) {
        for (int i=0;i<height;i++) {
            for (int j=0;j<width;j++) {
                const GridPoint gp(i,j);
                if (other(gp)) {
                    T* other_item_ptr=other(gp).get()->clone();
                    const std::shared_ptr<T> item_copy(other_item_ptr);
                    (*this)(gp) = std::shared_ptr<T>(item_copy);
                }
            }
        }
    }

    template<class T>
    Board<T>::~Board() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                const GridPoint gp(i,j);
                (*this)(gp)=nullptr;
            }
        }
    }

    template<class T>
    int Board<T>::getHeight() const{
        return this->height;
    }

    template<class T>
    int Board<T>::getWidth() const{
        return this->width;
    }

    template<class T>
    std::shared_ptr<T>& Board<T>::operator()(const GridPoint& gp) {
        int cell = this->width * gp.row + gp.col;
        return this->board.at(cell);
    }

    template<class T>
    const std::shared_ptr<T>& Board<T>::operator()(const GridPoint & gp) const {
        int cell = this->width * gp.row + gp.col;
        return this->board.at(cell);
    }

    template<class T>
    Board<T>& Board<T>::operator=(const Board& other) {
        if(this==&other){
            return *this;
        }
        height = other.height;
        width = other.width;
        board = std::vector<std::shared_ptr<T>>(other.getBoardSize(), nullptr);
        for (int i=0;i<height;i++) {
            for (int j=0;j<width;j++) {
                const GridPoint gp(i,j);
                T* other_item = (other(gp).get()->clone());
                (*this)(gp) = std::shared_ptr<T>(other_item);
            }
        }
        return *this;
    }

    template<class T>
    void Board<T>::addItem(const GridPoint& gp, std::shared_ptr<T> item) {
        if (!this->isCellLegal(gp)){
            throw IllegalCell();
        }
        if((*this)(gp) != nullptr){
            throw CellOccupied();
        }
        (*this)(gp) = item;
    }

    template<class T>
    void Board<T>::removeItem(const GridPoint& gp) {
        (*this)(gp)= nullptr;
    }

    template<class T>
    void Board<T>::moveItem(const GridPoint& src_gp, const GridPoint& dst_gp) {
        if(!this->isCellLegal(src_gp) || !this->isCellLegal(dst_gp)){
            throw IllegalCell();
        }
        std::shared_ptr<T> src_cell=(*this)(src_gp);
        std::shared_ptr<T> dst_cell=(*this)(dst_gp);
        if(src_cell == nullptr){
            throw CellEmpty();
        }
        if(!(dst_cell == nullptr)){
            throw CellOccupied();
        }
        (*this)(src_gp)=nullptr;
        (*this)(dst_gp)=src_cell;
    }

    template<class T>
    bool Board<T>::isCellLegal(const GridPoint& gp) {
        return !(gp.row<0 || gp.row >= this->height || gp.col<0 || gp.col >= this->width);
    }

    template<class T>
    int Board<T>::getBoardSize() const {
        return this->height * this->width;
    }
}
#endif //EX2_BOARD_H