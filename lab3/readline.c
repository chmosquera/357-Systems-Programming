#include <stdio.h>
#include <stdlib.h>
#include "readline.h"

char * readline(FILE * file){
    

    int size = 20;
    int cnt = 0;

    char *line;
    char c = NULL;
    line = (char *) malloc(sizeof(char) * size);

    c = fgetc(file);
    if (c == EOF && line[0] == '\0') {
        return NULL;
    }

    ++cnt;
    while (c != '\n' && c!= EOF) {
        if (cnt >=  size-1) { /* Array is not big enough, must realloc */
            char *temp = NULL;
            size = size * 2;
            temp = (char *) realloc(line, size);
            if (temp == NULL) { /*if realloc was not able to allocate memory*/
               exit(-1);
            }
            line = temp;
        }

        line[cnt-1] = c;
        c = fgetc(file);
        ++cnt;
    }
    
    line[cnt] = '\0';

    return line;
}
