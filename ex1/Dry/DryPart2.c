#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* foo(char* str, int* x) {  // Convention error 1: Function has non-informative name for function,
                                // it should be described as a verb, i.e. 'stringRevert'
                                // Convention error 2: x has non-informative name for variable, should be 'length'/'size'
    //coding error - required check if str is NULL
    char* str2;
    int i;
    x = strlen(str);//coding error: strlen return value should be inserted as x content, meaning *x
    str2 = malloc(*x);// coding error : requires one more space for '\0'
    //coding error: required check if allocation succeeded
    for (i = 0; i < *x; i++) // convention error: required '{}' even if block is only one line
        str2[i] = str[*x - i];// coding error: because of string-terminator character, it should be str2[i] = str[*x-i-1];
    if (*x % 2 == 0) {
        printf("%s", str);
    }
    if (*x % 2 != 0)
    {
        printf("%s", str2);
    }
    return str2;
}