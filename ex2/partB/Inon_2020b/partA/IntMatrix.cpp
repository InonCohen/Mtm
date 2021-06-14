
#include "IntMatrix.h"
#include <assert.h>
#define BIGGER '>'
#define SMALLER '<'
#define EQUAL '='
#define NOT_EQUAL '!'
#define BIG_EQUAL '#'
#define SMALL_EQUAL '%'

using mtm::IntMatrix;
namespace mtm {
    IntMatrix::IntMatrix(Dimensions dim, int initial_val) :
            dim(dim), matrix(new int[dim.getRow() * dim.getCol()]), initial_val(initial_val) {
        int size = dim.getRow() * dim.getCol();
        for (int i = 0; i < size; i++) {
            matrix[i] = initial_val;
        }
    }

    IntMatrix &IntMatrix::operator=(const IntMatrix &int_matrix) {
        if (this == &int_matrix) {
            return *this;
        }
        delete[] matrix;
        int new_row = int_matrix.dim.getRow();
        int new_col = int_matrix.dim.getCol();
        dim = int_matrix.dim;
        matrix = new int[new_row * new_col];
        initial_val = int_matrix.initial_val;
        for (int i = 0; i < new_row * new_col; i++) {
            matrix[i] = int_matrix.matrix[i];
        }
        return *this;
    }

    IntMatrix::IntMatrix(const IntMatrix &int_matrix) : dim(int_matrix.dim),
                                                        matrix(new int[int_matrix.dim.getRow() *
                                                                       int_matrix.dim.getCol()]),
                                                        initial_val(int_matrix.initial_val) {
        int size = dim.getRow() * dim.getCol();
        for (int i = 0; i < size; i++) {
            matrix[i] = int_matrix.matrix[i];
        }
    }

    IntMatrix::~IntMatrix() {
        delete[] matrix;
    }

    IntMatrix IntMatrix::Identity(unsigned int size) {
        IntMatrix identity(Dimensions(size, size));
        for (unsigned int i = 0; i < size * size; i += (size + 1)) {
            identity.matrix[i] = 1;
        }
        return identity;
    }

    const int IntMatrix::height() const {
        return this->dim.getRow();
    }

    const int IntMatrix::width() const {
        return this->dim.getCol();
    }

    const int IntMatrix::size() const {
        return this->height() * this->width();
    }

    IntMatrix IntMatrix::transpose() const {
        IntMatrix transposed_matrix(Dimensions(this->width(), this->height()));
        int count = 0;
        int new_height = transposed_matrix.height();
        int new_width = transposed_matrix.width();
        int new_size = new_height * new_width;
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < new_size; j += new_height) {
                transposed_matrix.matrix[count] = this->matrix[i + j];
                count++;
            }
        }
        return transposed_matrix;
    }

    int &IntMatrix::operator()(int row, int col) {
        int cell = this->width() * row + col;
        return this->matrix[cell];
    }

    const int &IntMatrix::operator()(int row, int col) const {
        int cell = this->width() * row + col;
        return this->matrix[cell];
    }


    IntMatrix operator+(const IntMatrix &matrix1, const IntMatrix &matrix2) {
        IntMatrix temp = matrix1;
        int height = temp.height();
        int width = temp.width();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                temp(i, j) = matrix1(i, j) + matrix2(i, j);
            }
        }
        return temp;
    }

    IntMatrix operator+(const int num, const IntMatrix int_matrix){
        IntMatrix num_matrix (Dimensions(int_matrix.height(),int_matrix.width()),num);
        num_matrix+=int_matrix;
        return num_matrix;
    }

    IntMatrix IntMatrix::operator+(const int num){
        IntMatrix new_matrix(Dimensions(this->height(),this->width()),num);
        new_matrix+=*this;
        return new_matrix;
    }

    IntMatrix IntMatrix::operator-() const {
        IntMatrix negative(this->dim);
        int size = negative.size();
        for (int i = 0; i < size; i++) {
            negative.matrix[i] = -1 * this->matrix[i];
        }
        return negative;
    }

    IntMatrix operator-(const IntMatrix &matrix1, const IntMatrix &matrix2) {
        IntMatrix negative(-matrix2);
        IntMatrix difference = matrix1 + negative;
        return difference;
    }

    //the following function was not required, I thought it might be helpful though
    IntMatrix &IntMatrix::operator+=(const IntMatrix &int_matrix) {
        int size = int_matrix.size();
        for (int i = 0; i < size; i++) {
            this->matrix[i] += int_matrix.matrix[i];
        }
        return *this;
    }

    IntMatrix& IntMatrix::operator+=(const int num){
        IntMatrix num_matrix(Dimensions(this->height(),this->width()),num);
        *this+=num_matrix;
        return *this;
    }

    IntMatrix operator+=(const int num, const IntMatrix int_matrix){
        IntMatrix num_matrix(Dimensions(int_matrix.height(),int_matrix.width()),num);
        num_matrix+=int_matrix;
        return num_matrix;
    }

    std::ostream &operator<<(std::ostream &os, const mtm::IntMatrix &int_matrix) {
        std::string str = mtm::printMatrix(int_matrix.matrix, int_matrix.dim);
        return os << str;
    }

    IntMatrix IntMatrix::operator==(int to_compare) {
        return IntMatrix::compareMatrix(*this, to_compare, EQUAL);
    }

    IntMatrix IntMatrix::operator!=(int to_compare) {
        return IntMatrix::compareMatrix(*this, to_compare, NOT_EQUAL);
    }

    IntMatrix IntMatrix::operator<=(int to_compare) {
        return IntMatrix::compareMatrix(*this, to_compare, SMALL_EQUAL);
    }

    IntMatrix IntMatrix::operator>=(int to_compare) {
        return IntMatrix::compareMatrix(*this, to_compare, BIG_EQUAL);
    }

    IntMatrix IntMatrix::operator<(int to_compare) {
        return IntMatrix::compareMatrix(*this, to_compare, SMALLER);
    }

    IntMatrix IntMatrix::operator>(int to_compare) {
        return IntMatrix::compareMatrix(*this, to_compare, BIGGER);
    }

     bool IntMatrix::compareInt(const int num1, const int num2, char sign) {
        if (sign == BIGGER) {
            return (num1 > num2);
        }
        if (sign == SMALLER) {
            return (num1 < num2);
        }
        if (sign == SMALL_EQUAL) {
            return (num1 <= num2);
        }
        if (sign == BIG_EQUAL) {
            return (num1 >= num2);
        }
        if (sign == EQUAL) {
            return (num1 == num2);
        }
        //if we get here, the sign is NOT_EQUAL, because we assume code correctness.
        // Otherwise we would have put an if(sign==NOT_EQUAL) and throw an error otherwise.
        return (num1 != num2);
    }

    IntMatrix IntMatrix::compareMatrix(const IntMatrix &int_matrix, int to_compare, char sign) {
        int height = int_matrix.height();
        int width = int_matrix.width();
        IntMatrix new_matrix(Dimensions(height, width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (compareInt(int_matrix(i, j), to_compare, sign)) { // compares matrix element according to sign
                    new_matrix(i, j) = 1;
                }
            }
        }
        return new_matrix;
    }

    bool all(const IntMatrix &int_matrix) {
        int height = int_matrix.height();
        int width = int_matrix.width();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (int_matrix(i, j) == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    bool any(const IntMatrix &int_matrix) {
        int height = int_matrix.height();
        int width = int_matrix.width();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (int_matrix(i, j) != 0) {
                    return true;
                }
            }
        }
        return false;
    }


    // initialization of iterator
    IntMatrix::iterator::iterator(IntMatrix* int_matrix, int index) : int_matrix(int_matrix), index(index) {}

    // operator *  (not sure if to leave const here as well or only for const iterator)
    int& IntMatrix::iterator::operator*()const {
    assert(index >= 0 && index < int_matrix->size());
    return int_matrix->matrix[index];
    }

    // begin implementation
    IntMatrix::iterator mtm::IntMatrix::begin(){
     return iterator(this, 0);
    }

    //end implementation
    IntMatrix::iterator mtm::IntMatrix::end(){
    return iterator(this,this->size());
    }

    // operator ++i
    IntMatrix::iterator& IntMatrix::iterator::operator++(){
        ++index;
        return *this;
    }

    //operator i++
    IntMatrix::iterator IntMatrix::iterator::operator++(int){
        iterator result = *this;
        ++*this;
        return result;
    }

    bool mtm::IntMatrix::iterator::operator==(iterator& iterator) {
        assert(int_matrix == iterator.int_matrix);
        return (index == iterator.index);
    }

    bool mtm::IntMatrix::iterator::operator!=(iterator it) {
        return !(*this == it);
    }


    // const iterator

    // begin implementation
    mtm::IntMatrix::const_iterator IntMatrix::begin()const {
     return const_iterator(this, 0);
    }

    //end implementation
    mtm::IntMatrix::const_iterator IntMatrix::end()const {
    return const_iterator(this,this->size());
    }
    //initialization

    IntMatrix::const_iterator::const_iterator(const IntMatrix* int_matrix, int index) :
     int_matrix(int_matrix),
     index(index)
    { }

    // operator *
    const int& IntMatrix::const_iterator::operator*() const {
    assert(index >= 0 && index < int_matrix->size());
    return int_matrix->matrix[index];
    }


    // operator==
    bool IntMatrix::const_iterator::operator==(const const_iterator& iterator) const {
        assert(int_matrix== iterator.int_matrix);
        return index == iterator.index;
    }

    // operator!=
    bool IntMatrix::const_iterator::operator!=(const const_iterator it) const {
        return !(*this == it);
    }

    // operator ++i
    IntMatrix::const_iterator& IntMatrix::const_iterator::operator++(){
        ++index;
        return *this;
    }

    //operator i++
    IntMatrix::const_iterator IntMatrix::const_iterator::operator++(int){
        const_iterator result = *this;
        ++*this;
        return result;
    }

}
