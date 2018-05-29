#include <stdio.h>
#include <ctype.h>
#include "part4.h"

void lower(char original[], char buffer[]) {
   
    char *pBuffer, *pOriginal;
    pBuffer = &buffer[0];
    pOriginal = &original[0];

    while (*pOriginal != '\0') {
        *pBuffer = tolower(*pOriginal);
        ++pOriginal;
        ++pBuffer;
    }
}

void str_lower_mutate(char str[]) {

    char *p;
    p = &str[0];

    while (*p != '\0') {
        *p = tolower(*p);
        ++p;
    }
}
