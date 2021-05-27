#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strUtils.h"

#define LENGTH_OF_ZERO_STRING 2

inline void nullifyString(char* str, size_t size){
    assert(str != NULL);
    memset(str, '\0', size);
}

inline char castDigitToChar(int digit) {
    assert(digit >= 0 && digit <= 9);
    char converted = (char)(digit + '0');
    return converted;
}

char* castIntToString(int num){
    if(num==0){
        char* str=malloc(LENGTH_OF_ZERO_STRING);
        if (str==NULL){
            return NULL;
        }
        str[0]='0';
        str[1]='\0';
        return str;
    }
    int numCopy=num, count=0;
    while (numCopy){//count the number of digits
        count++;
        numCopy/=10;
    }
    char* str=(char*)malloc((count) + 1);//+1 is for the '\0'
    if (str==NULL){
        return NULL;
    }
    nullifyString(str,count+1);
    for(int i=count-1;i>=0;i--){
        str[i]= castDigitToChar(num % 10);
        num/=10;
    }
    return str;
}

