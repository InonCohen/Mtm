#ifndef HW3_MATRIX_H
#define HW3_MATRIX_H

#include "Auxiliaries.h"
#include "Exceptions.h"
#include <string>

using std::cout;
using std::endl;
/*
partB General Notes:
    1. This is the templatic version of partA, added mostly templatic behavior and exception handling.
    2. There is no .cpp file here - template is static-binding-polymorphisem.
        So,  although mergeing between declration and implementation is an option, I chose to write it separatly, conventionally
    3. Further to the previous note, I have added comments "Declaration" and "Implementation" for enhanced readabilty.
    4. On contray to partA addition and subtraction (matrix-matrix or matrix-scalar) ARE NON-COMMUTATIVE necessarily! (i.e. string matrices).
    5. Friend functions are non-templatic functions by nature, so I avoided friend as much as I can here, 
        For more information see: https://web.mst.edu/~nmjxv3/articles/templates.html.
        The only friend here is "operator<<" which implemented within Matrix.h
        (one of the approaches to this problem, see: "Approach #3" on the link above).
    6. Class defined inside a template (i.e. class Matrix<T>::iterator) should declare in its signature
    it's a "typename" function everytime we want to refer *it.
*/
namespace mtm{ 
    // Declaration   
    // class Matrix<T> : Declartion
    template <class T>
    class Matrix{
        private:
            Dimensions dims;
            T* data;
            
            friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat){
                return printMatrix(os, mat.begin(), mat.end(), mat.width());
            }
        public:
            explicit Matrix(Dimensions dims, T=T());
            Matrix(const Matrix<T>&);
            ~Matrix();
            Matrix<T>& operator=(const Matrix<T>&);
            
            class AccessIllegalElement;
            class IllegalInitialization;
            class DimensionMismatch;        
            
            int height() const;
            int width() const;
            int size() const;

            static Matrix<T> Diagonal(int, T);
            Matrix<T> transpose() const;  

            class iterator;
            iterator begin();
            iterator end();
            class const_iterator;
            const_iterator begin() const;
            const_iterator end() const;

            Matrix<T> operator-() const;
            Matrix<T> operator+(const Matrix<T>&) const;
            Matrix<T> operator-(const Matrix<T>&) const;
            
            Matrix<bool> operator<(const T) const;
            Matrix<bool> operator<=(const T) const;
            Matrix<bool> operator>(const T) const;
            Matrix<bool> operator>=(const T) const;
            Matrix<bool> operator==(const T) const;
            Matrix<bool> operator!=(const T) const;
                    
            Matrix<T>& operator+=(const T);
            T& operator()(int, int);
            const T& operator()(int, int) const;

            template<class Callable>
            Matrix<T> apply(Callable c) const;

        };
    // class iterator : Declartion
    template <class T>
    class Matrix<T>::iterator {
        private:
            Matrix<T>* mat;
            int index;
            
            iterator(Matrix<T>* , int);
            friend class Matrix<T>;
        
        public:
            
            iterator(const iterator&) = default;
            iterator& operator=(const iterator&) = default;
            
            T& operator*() const;
            iterator& operator++();
            iterator operator++(int);
            bool operator==(const iterator&) const;
            bool operator!=(const iterator&) const;

    };
    // class const_iterator : Declartion
    template <class T>
    class Matrix<T>::const_iterator {
        private:
            const Matrix<T>* mat;
            int index;
    
            const_iterator(const Matrix<T>*, int);
            friend class Matrix<T>;
        
        public:
            const_iterator(const const_iterator&) = default;
            const_iterator& operator=(const const_iterator&) = default;
            
            const T& operator*() const;
            const_iterator& operator++();
            const_iterator operator++(int);
            bool operator==(const const_iterator&) const;
            bool operator!=(const const_iterator&) const;
    };
    // end Declaration

    // Implementation
    // Exceptions : implementation
    template <class T>
    class Matrix<T>::AccessIllegalElement: public Exception{        
        public:
            AccessIllegalElement() = default;
            ~AccessIllegalElement() = default;
            const char* what() const noexcept{
                return "Mtm matrix error: An attempt to access an illegal element";
            };
        };
    template <class T>
    class Matrix<T>::IllegalInitialization: public Exception{
        
        public:
            IllegalInitialization() = default;
            ~IllegalInitialization() = default;
            const char* what() const noexcept{
                return "Mtm matrix error: Illegal initialization values";
            };
        };
    template <class T>
    class Matrix<T>::DimensionMismatch: public Exception{
        Dimensions left, right;
        std::string msg; 

        public:
            DimensionMismatch(Dimensions left, Dimensions right): left(left), right(right){
                msg = "Mtm matrix error: Dimension mismatch: " + left.toString() + " " + right.toString();
                }
            
            const char* what() const noexcept{
                return msg.c_str();
            }
        };

    // class iterator : implementation
    template <class T>
    Matrix<T>::iterator::iterator(Matrix<T>* mat, int index) : mat(mat), index(index){}
    template <class T>    
    T& Matrix<T>::iterator::operator*() const{
        /*
        Throw exceptions: 
            1. AccessIllegalElement if trying to get a consumed iterator.
        Note: C/C++ compiler has no functionality of outOfBound access to array! it's undefined behavior.
        */
        if (this->index >= this->mat->size()){
           throw Matrix<T>::AccessIllegalElement();
           }
        return this->mat->data[index];
    }
    template <class T>
    typename Matrix<T>::iterator& Matrix<T>::iterator::operator++(){
        ++this->index;
        return *this;
    }
    template <class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int){
        iterator result = *this;
        ++(*this); // using prefix operator: incrementing this->index
        return result;
    }
    template <class T>
    bool Matrix<T>::iterator::operator==(const iterator& it) const{
        return index == it.index;
    }
    template <class T>
    bool Matrix<T>::iterator::operator!=(const iterator& it) const{
        return !(*this == it);
    }
    template <class T>
    typename Matrix<T>::iterator Matrix<T>::begin() {
        return iterator(this, 0);
    }
    template <class T>
    typename Matrix<T>::iterator Matrix<T>::end(){
        return iterator(this, this->size());
    }
    
    // class const_iterator : implementation
    template <class T>
    Matrix<T>::const_iterator::const_iterator(const Matrix<T>* mat, int index) : mat(mat), index(index){}
    template <class T>
    const T& Matrix<T>::const_iterator::operator*() const{
        /*
        Throw exceptions: 
            1. AccessIllegalElement if trying to get a consumed iterator.
        Note: C/C++ compiler has no functionality of outOfBound access to array! it's undefined behavior.
        */
        if (this->index >= this->mat->size()){
           throw Matrix<T>::AccessIllegalElement();
           }
        return this->mat->data[index];
    }
    template <class T>   
    typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++(){
        ++this->index;
        return *this;
    }
    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int){
        const_iterator result = *this;
        ++(*this); // using prefix operator: incrementing this->index
        return result;
    }
    template <class T>
    bool Matrix<T>::const_iterator::operator==(const const_iterator& it) const{
        return index == it.index;
    }
    template <class T>
    bool Matrix<T>::const_iterator::operator!=(const const_iterator& it) const{
        return !(*this == it);
    }
    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::begin() const{
        return const_iterator(this, 0);
    }
    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::end() const{
        return const_iterator(this, this->size());
    }


    // Matrix<T> Constructor, Destructor, Copy Constructor : Implementation
    template <class T>
    Matrix<T>::Matrix(Dimensions dims, T value): dims(dims){
        /*Throw exceptions:
            1. dims are non-negative: throw Matrix<t>::IllegalInitialization
            2. failed to allocate data: throw std::bad_alloc
        */
        if (!((this->height() > 0) and (this->width() > 0))){
            throw IllegalInitialization();
        }
        
        this->data = new T[size()];
        for (int i=0; i < this->size(); ++i){
            data[i] = value;
        } 
    }
    template <class T>
    Matrix<T>::Matrix(const Matrix<T>& other): 
        dims(other.dims),
        data(new T[other.size()])
        {
        for (int i=0; i < this->size(); ++i){
            this->data[i] = other.data[i];
        }
    }
    template <class T>
    Matrix<T>::~Matrix(){
        delete[] data;
    } 
    
    // Matrix<T> properties : Implementation
    template <class T>
    int Matrix<T>::height() const{
        return this->dims.getRow();
    }
    template <class T>
    int Matrix<T>::width() const{
        return this->dims.getCol();
    }
    template <class T>
    int Matrix<T>::size() const{
        return this->height() * this->width();
    }

    template <class T>
    Matrix<T> Matrix<T>::Diagonal(int n, T scalar)
    {
        /*Throw exceptions:
            1. n < 0: throw Matrix<t>::IllegalInitialization
            2. failed to allocate data: throw std::bad_alloc
        */
        Matrix<T> result = Matrix(Dimensions(n, n));
             for (int i=0; i < result.height(); ++i){
        result(i, i) = scalar;
    }
    return result;
    }
    template <class T>
    Matrix<T> Matrix<T>::transpose() const{
        Dimensions transpoed_dims = Dimensions(this->width(), this->height());
        Matrix<T> result = Matrix<T>(transpoed_dims);
        for (int row = 0; row < this->height(); ++row){
            for (int col = 0; col < this->width(); ++col){
                result(col,row) = (*this)(row, col);
            }
        }
        return result;
    }

    // Matrix<T> operators : Implementation
    // Access and Assiggnment Operators: Implementation
    template <class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T> &other){
        if (this == &other){
            return *this;
        }     
        delete[] this->data;
        
        this->dims = other.dims;
        this->data = new T[other.size()];
        
        for (int i = 0; i < this->size(); i++){
        this->data[i] = other.data[i];
        }
        return *this;
    }
    template <class T>
    T& Matrix<T>::operator()(int row, int col){
        if (!((0 <= row) and (row < this->height()) and (0 <= col) and (col < this->width()))){
            throw AccessIllegalElement();
        }
        return this->data[row * this->width() + col];
    }
    template <class T>
    const T& Matrix<T>::operator()(int row, int col) const{
        if (!((0 <= row) and (row < this->height()) and (0 <= col) and (col < this->width()))){
            throw AccessIllegalElement();
        }
        return this->data[row * this->width() + col];
    }

    // Marix-Matrix Addition and Subtraction Operators : Implementation
    template <class T>
    Matrix<T> Matrix<T>::operator-() const{
        Matrix<T> result = Matrix<T>(*this);
        for (int i=0; i < result.size(); ++i){
            result.data[i] = -result.data[i];
        }   
        return result;
}
    template <class T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const{
    	/*Throw exceptions:
            1. Matrix<T>::DimensionMismatch if dimensions of given matrices are different.
        */
        if (this->dims != other.dims){
            throw Matrix<T>::DimensionMismatch(this->dims, other.dims);
        }
        Matrix<T> result = Matrix<T>(*this);
        for (int i=0; i<size(); i++){
            result.data[i] = this->data[i] + other.data[i];
        }
        return result;
    }
    template <class T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const{
    	/*Throw exceptions:
            1. Matrix<T>::DimensionMismatch if mat1.size != mat2.size
        */
        if (this->dims != other.dims){
            throw Matrix<T>::DimensionMismatch(this->dims, other.dims);
        }

        return (*this) + (-other);
    }

    // Matrix-Scalar NON-COMMUTATIVE Addition Operators: Implementation
    template <class T>
    Matrix<T>& Matrix<T>::operator+=(T scalar){
        for (int i=0; i<this->size(); ++i){
            this->data[i] += scalar;
        }
        return (*this);
    }
    template <class T>
    Matrix<T> operator+(const Matrix<T>& mat, T scalar){
        Matrix<T> result = Matrix<T>(mat);
        return (result += scalar);
    }
    
    template <class T>
    Matrix<T> operator+(T scalar, const Matrix<T>& mat){
        Matrix<T> result = Matrix<T>(mat);
        for (int row = 0; row < result.height(); ++row){
            for (int col = 0; col < result.width(); ++col){
                result(row, col) = scalar + result(row, col);
            }
        }
        return result;
    }
    
    // Boolean Operators : Implementation
    /* 
    Note: can't access directly to Matrix<bool>.data because it's now 
    a different object from the generic Matrix<T>, so accessing via operator().
    */
    template <class T>
    Matrix<bool> Matrix<T>::operator<(const T scalar) const{
        Matrix<bool> result = Matrix<bool>(this->dims);
     
        for (int row = 0; row < result.height(); ++row){
            for (int col = 0; col < result.width(); ++col){
                result(row, col) = ((*this)(row, col) < scalar);
            }
        }
        return result;
    }
    template <class T>
    Matrix<bool> Matrix<T>::operator>=(const T scalar) const{
        Matrix<bool> result = Matrix<bool>(this->dims);
     
        for (int row = 0; row < result.height(); ++row){
            for (int col = 0; col < result.width(); ++col){
                result(row, col) = ((*this)(row, col) >= scalar);
            }
        }
        return result;
    }
    template <class T>
    Matrix<bool> Matrix<T>::operator>(const T scalar) const{
        Matrix<bool> result = Matrix<bool>(this->dims);
     
        for (int row = 0; row < result.height(); ++row){
            for (int col = 0; col < result.width(); ++col){
                result(row, col) = ((*this)(row, col) > scalar);
            }
        }
        return result;
    } 
    template <class T>
    Matrix<bool> Matrix<T>::operator<=(const T scalar) const{
        Matrix<bool> result = Matrix<bool>(this->dims);
     
        for (int row = 0; row < result.height(); ++row){
            for (int col = 0; col < result.width(); ++col){
                result(row, col) = ((*this)(row, col) <= scalar);
            }
        }
        return result;
    }
    template <class T>
    Matrix<bool> Matrix<T>::operator==(const T scalar) const{
        Matrix<bool> result = Matrix<bool>(this->dims);
     
        for (int row = 0; row < result.height(); ++row){
            for (int col = 0; col < result.width(); ++col){
                result(row, col) = ((*this)(row, col) == scalar);
            }
        }
        return result;
    } 
    template <class T>
    Matrix<bool> Matrix<T>::operator!=(const T scalar) const{
        Matrix<bool> result = Matrix<bool>(this->dims);
     
        for (int row = 0; row < result.height(); ++row){
            for (int col = 0; col < result.width(); ++col){
                result(row, col) = ((*this)(row, col) != scalar);
            }
        }
        return result;
    }
   
    template <class T>
    bool all(const Matrix<T>& mat){
        for (int row = 0; row < mat.height(); ++row){
            for (int col = 0; col < mat.width(); ++col){
                if (!bool(mat(row,col))){
                    return false;
                }
            }
        }
        return true;
    }
    template <class T>
    bool any(const Matrix<T>& mat){
        for (int row = 0; row < mat.height(); ++row){
            for (int col = 0; col < mat.width(); ++col){
                if (bool(mat(row,col))){
                    return true;
                }
            }
        }
        return false;
    }

    template <class T>
    template <class Callable>
    Matrix<T> Matrix<T>::apply(Callable func) const{
        Matrix<T> result = Matrix<T>(*this);
        for (int i=0; i<this->size(); i++){
            result.data[i] = func(this->data[i]);
        }

        return result;
    }
    // end Implementation
}
#endif
