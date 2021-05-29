#ifndef EX1_STRUTILS_H
#define EX1_STRUTILS_H

#define ID_SEP "_"

void nullifyString(char* str, size_t size);
char castDigitToChar(int digit);
char* castIntToString(int num);
char* createEmptyString(size_t size);
void freeAll(void* elem1, void* elem2, void* elem3, void* elem4);

#endif //EX1_STRUTILS_H
