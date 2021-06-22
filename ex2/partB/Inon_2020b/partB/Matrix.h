#ifndef PARTB_PARTB_H
#define PARTB_PARTB_H
#include <assert.h>
#include <string>
#include "Auxiliaries.h"
#define BIGGER '>'
#define SMALLER '<'
#define EQUAL '='
#define NOT_EQUAL '!'
#define BIG_EQUAL '#'
#define SMALL_EQUAL '%'

namespace mtm{
    template <class T>
    class Matrix{
        Dimensions dim;
        T* matrix;
        T initial_val;
		/**
			 * //Matrix<T>& operator+=(const Matrix<T>& mat)//:
			 * - recieves const matrix T parameter by reference.
			 * - adds recieved matrix to given matrix (this).
			 * - returns the given matrix by reference after summation.
			 * - matrix mat remains unchanged.
			 *
			 * Template Requirements:
			 *  T += operator.
			 * ~T() destructor
			  */ 
        Matrix<T>& operator+=(const Matrix<T>& mat);
    public:
                    // Matrix exceptions//
        /**
			 * all classes inherit from std::exception
			  */
        class AccessIllegalElement: public std::exception{
        public:

            const char* what() const noexcept {
                return "Mtm matrix error: An attempt to access an illegal element";
            }
        };
        class IllegalInitialization: public std::exception{
        public:
            const char* what() const noexcept {
                return "Mtm matrix error: Illegal initialization values";
            }
        };
        class DimensionMismatch: public std::exception {
            const std::string str;
        public:
            DimensionMismatch(const std::string first, const std::string second):
                    str("Mtm matrix error: Dimension mismatch: "+first+" "+second){};
            ~DimensionMismatch()= default;
            const char* what() const noexcept {
                return str.c_str();
            }
        };
        /**
			 * //Matrix<T>(Dimensions dim, T initial_value=T())//:
			 * Matrix<T> constructor.
			 * recieves dimension of matrix param and initial value of type T.
			 * constructs Matrix<T> , each element set to inital_value.
			 *
			 * Template Requirements:
			 * - T() constructor with no parameters.
			 * - assignment operator.
			 * -~T() destructor
			  */
        Matrix<T>(Dimensions& dim, T initial_val= T());
        /**
             * //Matrix<T>(const Matrix<T> &matrix)//:
             * - Matrix<T> copy constructor
             *
             * Template Requirements:
              * - T() constructor with no parameters.
              * - assignment operator.
              * -~T() destructor
              */
        Matrix<T>(const Matrix<T> &matrix);
        /**
             * //~Matrix()//:
             * - Matrix destructor.
             *
             * Template Requirements:
             * T destructor
              */
        ~Matrix();
        /**
             * //Matrix<T> &operator=(const Matrix<T> &matrix)//:
             * - Matrix<T> assignment operator
             *
             * Template Requirements:
              * - T() constructor with no parameters.
              *  T assignment operator.
              *  ~T() destructor
              */
        Matrix<T> &operator=(const Matrix<T> &matrix);
        /**
             * //static Matrix<T> Diagonal(int dim, T val)//:
             * - creates a diagonal matrix, each element of diagonal set to val.
             * - dimensions of matrix is dim.
             *
             * Template Requirements:
              * - T() constructor with no parameters.
              *  T assignment operator.
              *  ~T() destructor
              */
        static Matrix<T> Diagonal(int dim, T val);

        /**
       * //const int height() constt//:
       * - returns number of rows in given matrix.
       * Template Requirements: none
        */
        const int height() const;
        /**
             * //const int width() constt//:
             * - returns number of columns in given matrix.
             * Template Requirements: none
              */
        const int width() const;
        /**
             * //const int size() constt//:
             * - returns number of (row*columns) in given matrix.
             * Template Requirements: none
              */
        const int size() const;

        /**
           * //Matrix<T> transpose() const//:
           * - returns a transposed matrix of given matrix (this).
           * - returned by value.
           * - given matrix remains unchanged .
           *
           * Template Requirements:
            * - T() constructor with no parameters.
            *  T assignment operator.
            *  ~T() destructor
            * T copy constructor
            */
        Matrix<T> transpose() const;

        /**
			 * //Matrix<T> operator-()const//:
			 * unary minus operator.
			 * returns new matrix (by value)
			 * each elements data is -data of given matrix.
			 * given matrix remains unchanged.
			 * Template Requirements:
			 * T() constructor with no parameters.
			 * T assignment operator (=).
			 *  ~T(): destructor.
			 *  operator- unary minus operator.
			 * T copy constructor
			 */
        Matrix<T> operator-()const;

        /**
			 * //matrix<T> operator+(const T val) const//:
			 * - recieves const val T parameter.
			 * - adds val to each element of given matrix.
			 * - returns new matrix (by value) where each element is result of summation.
			 * - given matrix (this) remains unchanged.
			 *
			 * Template Requirements:
			 *  T() constructor with no parameters.
			 *  T + operator
			 *  T assignment (=) operator.
			 * ~T() destructor
			 * T copy constructor
			  */
        Matrix<T> operator+(const T val) const;

        /**
			 * //Matrix<T>& operator+=(const T val)//:
			 * - receives const matrix T parameter by reference.
			 * - adds received matrix to given matrix (this).
			 * - returns the given matrix by reference after summation.
			 * - matrix mat remains anchanged.
			 *
			 * Template Requirements:
			 *
			 *  T += operator.
			 * ~T() destructor
			  */
        Matrix<T>& operator+=(const T val);

        /**
			 * //T& operator()(int row, int col)//:
			 * returns element of received row and col in given matrix.
			 * Template Requirements: none
			 */
        T& operator()(int row, int col);
        /**
         * returns element of received row and col in given matrix.
         * Template Requirements: none
         */
        const T& operator()(int row, int col) const;

        /** //logical operator comparison functions://
		//Matrix<bool> operator(T to_compare)//:
		- recieves paramter to compare with matrix (T).
		- returns matrix in which each element is the result of the logical comparison (1 if true 0 if false).
		- dimensions of matrix are dimensions of the compared matrix (of *this matrix).
		- matrix is returned by value.
		* Template Requirements:
			 *  T() constructor with no parameters.
			 *  T assignment operator (=).
			 *  ~T(): destructor.
			 * T copy constructor
			 *  T operator of logical comparison (matching operator for every function):
			 * (==,!=,<=,>=,<,>)
		*/
        Matrix<bool> operator==(const T to_compare) const;
        Matrix<bool> operator!=(const T to_compare) const;
        Matrix<bool> operator<=(const T to_compare) const;
        Matrix<bool> operator>=(const T to_compare) const;
        Matrix<bool> operator<(const T to_compare) const;
        Matrix<bool> operator>(const T to_compare) const;

        // iterator and const iterator classes declared as members of class Matrix://
        /**
        -iterator class: a class to iterate over elements of Matrix<T>.
        - const iterator class: a class to iterate over elements of a const Matrix<T>.
        */
        class iterator;
        class const_iterator;
        // Matrix::iterator begin()//
        /**
        - returns iterator pointing to first element of Matrix<T>.
        * requirements:
        - constructor for class iterator.
        */
        Matrix::iterator begin(){
            return iterator(this,0);
        }
        // Matrix::iterator end()//
        /**
        - returns iterator pointing to "end" of matrix.
        * requirements:
        - constructor for class iterator.
        */
        Matrix::iterator end(){
            return iterator(this,this->size());
        }
        // Matrix::const_iterator begin() const//
        /**
        - returns const iterator pointing to first element of Matrix.
        - element remains unchanged since this parameter is const.
        * requirements:
        - constructor for class const iterator
        */
        Matrix::const_iterator begin() const{
            return const_iterator(this,0);
        }
        // mtm::IntMatrix::const_iterator end() const//
        /**
        - returns const iterator pointing to "end" of matrix.
        * requirements:
        - constructor for class const iterator
        */
        Matrix::const_iterator end() const{
            return const_iterator(this,this->size());
        }

        /**
			 * //Matrix<T> apply(Function func) const//:
			 * - apply function that recieves a paramater that is a function.
			 * - function is applied to each element of the given matrix.
			 * - result is assigned to new matrix of same dimensions as given matrix.
			 * - new matrix is returned by value,original matrix remains unchanged.
			 * Template Requirements:
			  *  T() default constructor.
			  *  T assignment operator.
			  *  ~T() destructor
			  * T copy constructor
			  */
        template<class Function>
        Matrix<T> apply(Function func) const;
    };
	
    template <class T>
    class Matrix<T>::iterator{
        Matrix* matrix;
        int index;
		/**
		//iterator(Matrix* matrix, int index)//:
		- constructor of iterator.
		- recieves Matrix* parameter and index parameter of type int.
		- not declared in public because we dont want our user to initialize iterator pointing to illegal address.
	 */
        iterator(Matrix* matrix, int index): matrix(matrix), index(index){};
        friend class Matrix<T>;
    public:
		/**
		//~iterator()=default//:
		- destructor of iterator class.
		- set to be default- will be called and determined by compiler.
	 */
        ~iterator()=default;
		/**
		//iterator(const iterator& it)=default//:
		- copy constructor of iterator class.
		- set to be default- will be called and determined by compiler.
	 */
        iterator(const iterator& it)=default;
		/**
		//T& operator*() const//:
		-returns element iterator is pointing at
		- iterator remains unchanged.
	 */
        T& operator*() const;
		/**
		//iterator& operator=(iterator& iterator)=default//:
		-assignment operator.
		- recieves iterator reference parameter.
		- set to be default, return iterator by reference.
	 */
        iterator& operator=(iterator& iterator)=default;
		/**
		//iterator& operator++()//:
		-prefix ++ operator.
		- returns iterator pointing to next element in matrix.
	 */
        iterator& operator++();
		/**
		//iterator operator++(int)//:
		-postfix ++ operator
		-advances iterators index by 1.
		- returns original iterator (*this) by value
	 */
        iterator operator++(int);//postfix operator
		/**
		//bool operator==(iterator& iterator)//:
		- compares two iterators.
		- returns true if they are pointing at same element (by index)
		- otherwise returns false.
	 */
        bool operator==(iterator& iterator);
		/**
		//bool operator!=(iterator iterator)//:
		- compares two iterators.
		- returns false if they are pointing at same element (by index)
		- otherwise returns true.
	 */
        bool operator!=(iterator iterator);
    };
	//implementation of const_iterator class//
    template <class T>
    class Matrix<T>:: const_iterator{
        const Matrix* matrix;
        int index;
		/**
	//iterator(const Matrix* int_matrix, int index)//:
	- constructor of const_iterator.
 */
        const_iterator(const Matrix* matrix, int index): matrix(matrix), index(index){};
        friend class Matrix<T>;
    public:
		/**
	//~const_iterator()=default//:
	- destructor of const_iterator class.
 */
        ~const_iterator()=default;
		/**
	   //T& operator*() const//:
	   -returns element iterator is pointing at as const.
	   - const_iterator remains unchanged.
	*/
        const T& operator*() const;
		/**
		//const_iterator(const const_iterator& const_it)=default//:
		- copy constructor of const_iterator class- set to default.
	 */
        const_iterator(const const_iterator& const_it)=default;
		/**
		//const_iterator& operator=(const_iterator& iterator)=default//:
		-assignment operator.
		- recieves const_iterator reference parameter.
		- set to be default, return const_iterator by reference.
	 */
        const_iterator& operator=(const_iterator& iterator)=default;
		/**
		//const_iterator& operator++()//:
		-prefix ++ operator.
		- returns const_iterator pointing to next element in matrix.
	 */
        const_iterator& operator++();
		/**
		//const_iterator operator++(int)//:
		-postfix ++ operator
		-advances const_iterators index by 1.
		- returns original const_iterator (*this) by value
	 */
        const_iterator operator++(int); 
		/**
		//bool operator==(const const_iterator& iterator) const//:
		- compares two const iterators.
		- returns true if they are pointing at same element (by index)
		- otherwise returns false.
	 */
        bool operator==(const const_iterator& iterator) const;
		/**
		//bool operator!=(const const_iterator& iterator) const//:
		- compares two const iterators.
		- returns false if they are pointing at same element (by index)
		- otherwise returns true.
	 */
        bool operator!=(const const_iterator it) const;
    };




	//implementation of Matrix class functions//

    template <class T>
    Matrix<T>::Matrix(Dimensions dim, T initial_val) :
            dim(dim),
            matrix(dim.getRow()<=0||dim.getCol()<=0? throw IllegalInitialization(): new T[dim.getRow()*dim.getCol()]),
    initial_val(initial_val) {
            int size = dim.getRow() * dim.getCol();
            for (int i = 0; i < size; i++) {
                matrix[i] = initial_val;
            }
    }

    template <class T>
    Matrix<T>::Matrix(const Matrix &mat) : dim(mat.dim),
                                              matrix(new T[mat.dim.getRow() * mat.dim.getCol()]),
                                              initial_val(mat.initial_val) {
        int size = dim.getRow() * dim.getCol();
        for (int i = 0; i < size; i++) {
            matrix[i] = mat.matrix[i];
        }
    }

    template <class T>
    Matrix<T>::~Matrix() {
        delete[] matrix;
    }


    template <class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix_t) {
        if (this == &matrix_t) {
            return *this;
        }
        delete[] matrix;
        int new_row = matrix_t.height();
        int new_col = matrix_t.width();
        dim = matrix_t.dim;
        matrix = new T[new_row * new_col];
        initial_val = matrix_t.initial_val;
        for (int i = 0; i < new_row * new_col; i++) {
            matrix[i] = matrix_t.matrix[i];
        }
        return *this;
    }

    template <class T>
    Matrix<T> Matrix<T>::Diagonal(int dim, T val){
        if (dim<=0){
            throw Matrix<T>::IllegalInitialization();
        }
        Matrix<T> new_diagonal(Dimensions(dim, dim));
        int size=new_diagonal.size();
        int width=new_diagonal.width();
        for(int i=0;i<size;i+=(width + 1)){
            new_diagonal.matrix[i] = val;
        }
        return new_diagonal;
    }

    template <class T>
    Matrix<T> Matrix<T>::transpose() const{
            Matrix<T> transposed_matrix(Dimensions(this->width(), this->height()));
            int count = 0;
            int new_height = transposed_matrix.height();
            //int new_width = transposed_matrix.width();
            int new_size = transposed_matrix.size();
            for (int i = 0; i < new_height; i++) {
                for (int j = 0; j < new_size; j += new_height) {
                    transposed_matrix.matrix[count] = this->matrix[i + j];
                    count++;
                }
            }
            return transposed_matrix;
        }

    template <class T>
    T& Matrix<T>::operator()(int row, int col) {
        if (row<0 || row>=this->height()||col<0 || col>=this->width()){
            throw Matrix<T>::AccessIllegalElement();
        }
        int cell = this->width() * row + col;
        return this->matrix[cell];
        }

    template <class T>
    const T& Matrix<T>::operator()(int row, int col) const {
        if (row<0 || row>=this->height()||col<0 || col>=this->width()){
            throw Matrix<T>::AccessIllegalElement();
        }
        int cell = this->width() * row + col;
        return this->matrix[cell];
    }

    template <class T>
    Matrix<T> operator+(const Matrix<T> &matrix1, const Matrix<T> &matrix2) {
        int height = matrix1.height();
        int width = matrix1.width();
        if((height!=matrix2.height())||width!=matrix2.width()){
            Dimensions dim1(height,width);
            Dimensions dim2(matrix2.height(),matrix2.width());
            throw typename Matrix<T>::DimensionMismatch(dim1.toString(),dim2.toString());
        }
        Matrix<T> temp = matrix1;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                temp(i, j) = matrix1(i, j) + matrix2(i, j);
            }
        }
        return temp;
    }

    template <class T>
    Matrix<T> operator+(const T val, const Matrix<T> mat){
        Matrix<T> val_matrix (Dimensions(mat.height(),mat.width()),val);
        val_matrix+=mat;
        return val_matrix;
    }

    template <class T>
    Matrix<T> Matrix<T>::operator+(const T val) const{
        Matrix<T> val_matrix (Dimensions(this->height(),this->width()),val);
        Matrix<T> result=*this+val_matrix;
        return result;
    }



    template <class T>
    Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& mat) {
        int height = this->height();
        int width = this->width();
        if((height!=mat.height())||width!=mat.width()){
            Dimensions dim1(height,width);
            Dimensions dim2(mat.height(),mat.width());
            throw typename Matrix<T>::DimensionMismatch(dim1.toString(),dim2.toString());
        }
        int size = mat.size();
        for (int i = 0; i < size; i++) {
            this->matrix[i] += mat.matrix[i];//we assume here that T has a += operator
        }
        return *this;
    }

    template <class T>
    Matrix<T>& Matrix<T>::operator+=(const T val){
        Matrix<T> val_matrix(Dimensions(this->height(),this->width()),val);
        *this+=val_matrix;
        return *this;
    }
    template <class T>
    Matrix<T> Matrix<T>::operator-() const {
            Matrix<T> negative_matrix(this->dim);
            int size = negative_matrix.size();
            for (int i = 0; i < size; i++) {
                negative_matrix.matrix[i] = -matrix[i];
            }
            return negative_matrix;
        }


    template <class T>
    Matrix<T> operator-(const Matrix<T>& mat1, const Matrix<T>& mat2) {
        Matrix<T> negative(-mat2);// we assume that T type has a negative value.
        Matrix<T> difference = mat1 + negative;
        return difference;
    }

    template <class T>
    Matrix<bool> Matrix<T>::operator==(const T to_compare) const {
            return compareMatrix(*this, to_compare, EQUAL);
        }

    template <class T>
        Matrix<bool> Matrix<T>::operator!=(const T to_compare) const {
            return compareMatrix(*this, to_compare, NOT_EQUAL);
        }

    template <class T>
        Matrix<bool> Matrix<T>::operator<=(const T to_compare) const {
            return compareMatrix(*this, to_compare, SMALL_EQUAL);
        }

    template <class T>
        Matrix<bool> Matrix<T>::operator>=(const T to_compare) const {
            return compareMatrix(*this, to_compare, BIG_EQUAL);
        }

    template <class T>
        Matrix<bool> Matrix<T>::operator<(const T to_compare) const {
            return compareMatrix(*this, to_compare, SMALLER);
        }

    template <class T>
        Matrix<bool> Matrix<T>::operator>(const T to_compare) const {
            return compareMatrix(*this, to_compare, BIGGER);
        }
		/**
		//static bool compareT(const T val1, const T val2, char sign)//:
		- This is a helping function for compareMatrix.
		- recieves paramter T val1: element of matrix that is compared.
		- paramter val 2 is the value that is compared with the element.
		- sign is a char set according to logical operator used.
		- returns boolean result of comparison (by logical operator).
		*Template requirements:
		* operators of logical comparison for T (>,<,<=,>=,==,!=)
		*/
    template <class T>
        static bool compareT(const T val1, const T val2, char sign) const {
            if (sign == BIGGER) {
                return (val1 > val2);
            }
            if (sign == SMALLER) {
                return (val1 < val2);
            }
            if (sign == SMALL_EQUAL) {
                return (val1 <= val2);
            }
            if (sign == BIG_EQUAL) {
                return (val1 >= val2);
            }
            if (sign == EQUAL) {
                return (val1 == val2);
            }
            //if we get here, the sign is NOT_EQUAL, because we assume code correctness.
            // Otherwise we would have put an if(sign==NOT_EQUAL) and throw an error otherwise.
            return (val1 != val2);
        }


    template <class T>
    bool all(const Matrix<T>& mat) {
        int height = mat.height();
        int width = mat.width();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if ((bool)mat(i, j) == false) {
                    return false;
                }
            }
        }
        return true;
    }

    template <class T>
    bool any(const Matrix<T> &mat) {
        int height = mat.height();
        int width = mat.width();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if ((bool)mat(i, j) != false) {
                    return true;
                }
            }
        }
        return false;
    }
    /**
            //static Matrix<bool> compareMatrix(const Matrix<T>& mat, T to_compare, char sign)//:
            - This is a helping function for logical comparison operator functions.
            - recieves a const matrix to compare (paramter by reference), an T val that it will be compared with.
            - parameter sign is determined by logical operator.
            - returns new matrix of same dimensions as  mat.
            - elements of matrix are the result of logical comparison between each element of mat and to_compare.
            - (1 if result is true and 0 if false).
            * Template requirements:
            * Matrix<bool> constructor.
            * operators of logical comparison for T (>,<,<=,>=,==,!=)
            * T assignment operator (=)
            * T copy constructor
            * ~T() destructor
            */
    template <class T>
    static Matrix<bool> compareMatrix(const Matrix<T>& mat, T to_compare, char sign) {
        int height = mat.height();
        int width = mat.width();
        Matrix<bool> new_matrix(Dimensions(height, width),false);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (compareT(mat(i, j), to_compare, sign)) {
                    new_matrix(i, j) = true;
                }
            }
        }
        return new_matrix;
    }
    template <class T>
    const int Matrix<T>::height() const {
        return this->dim.getRow();
    }
    template <class T>
    const int Matrix<T>::width() const {
        return this->dim.getCol();
    }
    template <class T>
    const int Matrix<T>::size() const {
        return this->height() * this->width();
    }

    template <class T>
    T& Matrix<T>::iterator::operator*() const{
        if(index < 0 || index >= matrix->size()){
            throw AccessIllegalElement();
        }
        return matrix->matrix[index];
    }
    // operator ++i
    template <class T>
    typename Matrix<T>::iterator& Matrix<T>::iterator::operator++(){
        ++index;
        return *this;
    }

    //operator i++
    template <class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int){
        iterator result = *this;
        ++*this;
        return result;
    }

    template <class T>
    bool mtm::Matrix<T>::iterator::operator==(iterator& iterator) {
        assert(matrix == iterator.matrix);
        return (index == iterator.index);
    }
    template <class T>
    bool mtm::Matrix<T>::iterator::operator!=(iterator it) {
        return !(*this == it);
    }
	
	/**
			 // std::ostream& operator<<(std::ostream &os, const mtm::Matrix<T>& matrix)//: 
			  output operator for Matrix<T>
			  * Template Requirements:
			  * - T copy constructor.
			  * - T() destructor.
			  * - operator output for T << .
			  */
    template <class T>
    std::ostream& operator<<(std::ostream &os, const mtm::Matrix<T>& matrix) {
        return printMatrix(os, matrix.begin(),matrix.end(), matrix.width());
    }

    // operator *
    template <class T>
    const T& Matrix<T>::const_iterator::operator*() const {
        if(index < 0 || index >= matrix->size()) {
            throw AccessIllegalElement();
        }
        return matrix->matrix[index];
    }


    // operator==
    template <class T>
    bool Matrix<T>::const_iterator::operator==(const const_iterator& iterator) const {
        assert(matrix== iterator.matrix);
        return (index == iterator.index);
    }

    // operator!=
    template <class T>
    bool Matrix<T>::const_iterator::operator!=(const const_iterator it) const {
        return !(*this == it);
    }

    // operator ++i
    template <class T>
    typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++(){
        ++index;
        return *this;
    }

    //operator i++
    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int){
        const_iterator result = *this;
        ++*this;
        return result;
    }

    template<class T>
    template<class Function>
    Matrix<T> Matrix<T>::apply(Function func) const{
        int width = this->width();
        int height = this->height();
        Dimensions dimensions(height, width);
        Matrix<T> result(dimensions);
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                T temp=(*this)(i,j);
                result(i,j) = func(temp);
            }
        }
        return result;
    }


}


#endif //PARTB_PARTB_H
