#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include "Character.h"
#include "Exceptions.h"


namespace mtm {
    template <class T>
    class Board{
        int height;
        int width;
        std::vector<std::shared_ptr<T>> board;
    public:
        Board(int height, int width);
        Board(const Board&);
        ~Board();
        Board& operator=(const Board&);
        std::shared_ptr<T>& operator()(const GridPoint&);
        const std::shared_ptr<T>& operator()(const GridPoint&) const;
        int getHeight() const;
        int getWidth() const;
        int getBoardSize() const;
        void addItem(const GridPoint&, std::shared_ptr<T>);
        void removeItem(const GridPoint&);
        void moveItem(const GridPoint&, const GridPoint&);
        bool isCellLegal(const GridPoint&);
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
    Board<T>& Board<T>::operator=(const Board<T>& other) {
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
#endif //BOARD_H
