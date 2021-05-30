#ifndef EX1_STRUTILS_H
#define EX1_STRUTILS_H

#define ID_SEP "_"

void nullifyString(char* str, size_t size);
char castDigitToChar(int digit);
char* castIntToString(int num);
char* createEmptyString(size_t size);
void freeAll(char* elem1,char* elem2,char* elem3,char* elem4);

#endif //EX1_STRUTILS_H
