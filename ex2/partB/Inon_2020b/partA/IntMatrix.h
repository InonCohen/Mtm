#include "Auxiliaries.h"
using mtm::Dimensions;

namespace mtm {
    class IntMatrix {
	private:
		Dimensions dim;
        int *matrix;
        int initial_val;
		static IntMatrix compareMatrix(const IntMatrix& int_matrix, int to_compare, char sign);
		/**
			//static bool compareInt(const int num1, const int num2, char sign)//:
			- This is a helping function for compareMatrix.
			- recieves paramter int num1: element of matrix that is compared.
			- paramter num 2 is the int that is compared with the element.
			- sign is a char set according to logical operator used.
			- returns boolean result of comparison (by logical operator).
			*/
		static bool compareInt(const int num1, const int num2, char sign);
		/**
			//operator+(const IntMatrix& matrix1, const IntMatrix& matrix2)//:
			- recieves parameters of two matrices as const reference.
			- sums two matrices and returns matrix of sum (by value).
			- we assume here that the summed matrices are of the same size.
			*/

    public:
		/**
		//IntMatrix(Dimensions dimensions, int inital_val=0)//:
		- constructor that recieves input of dimensions and initializing int.
		- constructs the matrix according to given dimensions all eךments in matrix seא to the initial_val
		- allocation of memory can fail, but we ignore this exception according to requirements of this excercise.
		- if no value passed, constructs matrix with given dimensions, all values zero.
		*/
        IntMatrix(Dimensions dim, int initial_val = 0);
		/**
		//IntMatrix(const IntMatrix &int_matrix)//:
		 -copy constructor for IntMatrix, recieves int_matrix reference.
		 -allocation of memory can fail, but we ignore this exception according to requirements of this excercise.
		*/
		IntMatrix(const IntMatrix &int_matrix);
		/**
		//static IntMatrix Identity(unsigned int size)//:
		- recieves unsigned int size.
		- constructs identity matrix with dimension of (size,size)
		- returns the matrix by value;
		*/
        static IntMatrix Identity(unsigned int size);
		/**
		//const int height() const//:
		- returns number of rows in matrix.
		*/
		const int height() const;
		/**
		//const int width() const//:
		- returns number of columns in matrix.
		*/
        const int width() const;
		/**
		//const int size() const//:
		- returns (number of rows* number of columns) in matrix.
		*/
        const int size() const;
		/**
		//IntMatrix transpose() const//:
		- constructs a transposed matrix of matrix "recieved" by this
		- returns the matrix by value.
		- original matrix remains unchanged..
		*/
        IntMatrix transpose() const;
		/**
		//~IntMatrix()//:
		-destructor of Intmatrix. deletes all data allocated.
		*/
        ~IntMatrix();
		/**
		//IntMatrix &operator=(const IntMatrix &int_matrix)//:
		-assignment operator.
		- recieves a const matrix parameter by reference, and assigns its values to given matrix.
		- returns given matrix. 
		- here aswell, failure of memory allocation is ignored due to requirements.
		*/
        IntMatrix &operator=(const IntMatrix &int_matrix);
		/**
		//IntMatrix& operator+=(const IntMatrix& int_matrix)//:
		- recieves const matrix reference paramter.
		- sums int_matrix recieved to (this) matrix, and returns result.
		- result returned by reference.
		*/
        IntMatrix& operator+=(const IntMatrix& int_matrix); 
		/**
		//IntMatrix& operator+=(const int num)//:
		- receives an int and adds it to all elements of matrix.
		- returns the matrix.
		*/
        IntMatrix& operator+=(const int num);
		/**
		//IntMatrix operator+(const int num)//:
		- receives an int to add to matrix.
		- returns matrix of same dimensions 
		*/
        IntMatrix operator+(const int num);
		/**
		//operator-()const//:
		- unary minus operator
		- returns a new matrix (by value).
		- elements of new matrix are elements of the given matrix multiplied by -1.
		- given matrix remains unchanged.
		*/
        IntMatrix operator-()const;
		/**
		//int& operator()(int row, int col)//:
		-recieves a row number (paramter) and column number (parameter) both of int type.
		- returns element in row and column, by reference.
		*/
        int& operator()(int row, int col);
		/**
		//const int& operator()(int row, int col) const//:
		-recieves a row number (paramter) and column number (parameter) both of int type.
		- returns element in row and column, as const int reference- read only.
		- this parameter is a const, therefore matrix remains unchanged.
		*/
        const int& operator()(int row, int col) const;
		/**
		//IntMatrix operator==(int to_compare)//:
		- recieves paramter to compare with matrix (int).
		- returns matrix in which each element is the result of the logical comparison (1 if true 0 if false).
		 dimensions of matrix are dimensions of the compared matrix (of *this matrix).
		- matrix is returned by value.
		*/
        IntMatrix operator==(int to_compare);
		/**
		//IntMatrix operator!=(int to_compare)//:
		- recieves paramter to compare with matrix (int).
		- returns matrix in which each element is the result of the logical comparison (1 if true 0 if false).
		- dimensions of matrix are dimensions of the compared matrix (of *this matrix).
		- matrix is returned by value.
		*/
        IntMatrix operator!=(int to_compare);
		/**
		//IntMatrix operator<=(int to_compare)//:
		- recieves paramter to compare with matrix (int).
		- returns matrix in which each element is the result of the logical comparison (1 if true 0 if false).
		- dimensions of matrix are dimensions of the compared matrix (of *this matrix).
		- matrix is returned by value.
		*/
        IntMatrix operator<=(int to_compare);
		/**
		//IntMatrix operator>=(int to_compare)//:
		- recieves paramter to compare with matrix (int).
		- returns matrix in which each element is the result of the logical comparison (1 if true 0 if false).
		-dimensions of matrix are dimensions of the compared matrix (of *this matrix).
		- matrix is returned by value.
		*/
        IntMatrix operator>=(int to_compare);
		/**
		//IntMatrix operator<(int to_compare)//:
		- recieves paramter to compare with matrix (int).
		- returns matrix in which each element is the result of the logical comparison (1 if true 0 if false).
		- dimensions of matrix are dimensions of the compared matrix (of *this matrix).
		- matrix is returned by value.
		*/
        IntMatrix operator<(int to_compare);
		/**
		//IntMatrix operator>(int to_compare)//:
		- recieves paramter to compare with matrix (int).
		- returns matrix in which each element is the result of the logical comparison (1 if true 0 if false).
		- dimensions of matrix are dimensions of the compared matrix (of *this matrix).
		- matrix is returned by value.
		*/
        IntMatrix operator>(int to_compare);
		/**
		//friend std::ostream &operator<<(std::ostream &os, const IntMatrix &int_matrix)//:
		- recieves paramter ostream by reference and matrix int_matrix by reference.
		- returns paramter ostream by reference..
		*/
        friend std::ostream &operator<<(std::ostream &os, const IntMatrix &int_matrix);
		// iterator and const iterator classes declared as members of class Intmatrix://
		/**
		-iterator class: a class to iterator over elements of a matrix.
		- const iterator class: a class to iterate over elements of a const matrix.
		*/
        class iterator;
        class const_iterator;

		// mtm::IntMatrix::iterator begin()//
		/**
		- returns iterator pointing to first element of matrix.
		*/
		mtm::IntMatrix::iterator begin();
		// mtm::IntMatrix::iterator end()//
		/**
		- returns iterator pointing to "end" of matrix.
		- "end" of matrix reffers to cell after last cell of matrix array.
		*/
        mtm::IntMatrix::iterator end();
		// mtm::IntMatrix::const_iterator begin() const//
		/**
		- returns const iterator pointing to first element of matrix.
		- element remains unchanged since this parameter is const.
		*/
        mtm::IntMatrix::const_iterator begin() const;
		// mtm::IntMatrix::const_iterator end() const//
		/**
		- returns const iterator pointing to "end" of matrix.
		- "end" of matrix reffers to cell after last cell of matrix array.
		*/
        mtm::IntMatrix::const_iterator end() const;

    };
	
	/**
		//static IntMatrix compareMatrix(const IntMatrix& int_matrix, int to_compare, char sign)//:
		- This is a helping function for logical comparison operator functions.
		- recieves a matrix to compare (paramter by reference), an int that it will be compared with.
		- parameter sign is determined by logical operator.
		- returns new matrix of same dimensions as  int_matrix. 
		- elements of matrix are the result of logical comparison between each element of int_matrix and to_compare.
		- (1 if result is true and 0 if false).
		*/
    IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);
	/**
		//operator+(const int num, const IntMatrix& matrix2)//:
		- recieves int paramter and const matrix reference.
		- returns a new matrix that is the result of adding num to each element of matrix2.
		- new matrix is returned by value.
		*/
    IntMatrix operator+(const int num, const IntMatrix int_matrix);
	/**
		//IntMatrix operator+=(const int num, const IntMatrix int_matrix)//:
		- recieves int paramter and const matrix.
		- returns a new matrix that is the result of summing num to each element in int_matrix.
		- new matrix is returned by value.
		*/
    IntMatrix operator+=(const int num, const IntMatrix int_matrix);
	/**
		//IntMatrix operator-(const IntMatrix& matrix1, const IntMatrix& matrix2)//:
		- recieves two const matrices by reference.
		- returns a matrix that is the result of subtracting the two matrices.
		- matrix returned by value.
		*/
    IntMatrix operator-(const IntMatrix& matrix1, const IntMatrix& matrix2);
	/**
		//bool all(const IntMatrix& int_matrix)//:
		-recieves const matrix by reference.
		-returns true if all matrix elements are not zeros.
		-returns false otherwise.
	 */
    bool all(const IntMatrix& int_matrix);
	/**
		//any(const IntMatrix& int_matrix//:
		-recieves const matrix by reference.
		-returns true if there is an element in the matrix not equal to zero.
		-returns false otherwise.
	 */
    bool any(const IntMatrix& int_matrix);

	//decleration of iterator and const iterator classes//
    class IntMatrix::iterator{
        IntMatrix* int_matrix;
        int index;
		/**
		//iterator(IntMatrix* int_matrix, int index)//:
		- constructor of iterator.
		- recieves IntMatrix* parameter and index parameter of type int.
		- not declared in public because we dont want our user to initialize iterator pointing to illegal address.
	 */
        iterator(IntMatrix* int_matrix, int index);
        friend class IntMatrix;
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
		//int& operator*() const//:
		-returns element iterator is pointing at
		- iterator remains unchanged.
	 */
        int& operator*()const;
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
	//const iterator class is designed to work with a const matrix, and const iterator
     class IntMatrix:: const_iterator{
        const IntMatrix* int_matrix;
        int index;
		/**
		//iterator(const IntMatrix* int_matrix, int index)//:
		- constructor of const_iterator.
	 */
        const_iterator(const IntMatrix* int_matrix, int index);
        friend class IntMatrix;
        
        public:
			/**
		//~const_iterator()=default//:
		- destructor of const_iterator class.
	 */
         ~const_iterator()=default;
		 /**
		//const int& operator*() const//:
		-returns element iterator is pointing at as const.
		- const_iterator remains unchanged.
	 */
        const int& operator*() const;
		/**
		//const_iterator(const const_iterator& it)=default//:
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
        const_iterator operator++(int); //postfix operator
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
    


}