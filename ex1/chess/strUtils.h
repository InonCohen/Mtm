#ifndef EX1_STRUTILS_H
#define EX1_STRUTILS_H

#define ID_SEP "_"

/**
* strUtils is an Auxiliary Class that holds functions which are used by multiple ADTs
* in order to create and manage strings.
*
*
* The following functions are available:
*   nullifyString		- Makes a given string empty.
*   castDigitToChar		- Makes a given digit of type int a string.
*   castIntToString		- Makes a given number of type int a string.
*   createEmptyString	- Deallocates 4 given strings.
*/

/**
* nullifyString: Makes a given string an empty string.
*
* @param str    - A string to nullify.
* @param size   - The size of the string
*/
void nullifyString(char* str, size_t size);

/**
* castDigitToChar: Casts a digit into a character.
*
* @param digit    - Digit to convert to char.
* @return
*   The casted number char.
*/
char castDigitToChar(int digit);

/**
* castIntToString: Casts a number into string.
*
* @param num    - Number to convert to string.
* @return
* 	NULL if the casting failed.
*   The string containing the casted number otherwise.
*/
char* castIntToString(int num);

/**
* createEmptyString: Creates ane empty string of given size.
*
* @param size   - Size of required empty strings.
* @return
* 	NULL if the casting failed or if size is non-positive.
*   The new empty string in length of size otherwise.
*/
char* createEmptyString(size_t size);

/**
* freeAll: Frees 4 given strings.
*
* @param str1    - A string to free.
* @param str2    - A string to free.
* @param str3    - A string to free.
* @param str4    - A string to free.
*/
void freeAll(char* elem1,char* elem2,char* elem3,char* elem4);

#endif //EX1_STRUTILS_H
