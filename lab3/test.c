#include <stdio.h>
#include "readline.h"
#include <stdlib.h>

int main(int argc, char  **argv){

    FILE *file = NULL;
    char *str = NULL;

    file = fopen(argv[1], "r");
    if (file == NULL) {
        exit(-1);
    }

    str = readline(file);
    while (str != NULL) {
        printf("%s\n",str);
        str = readline(file);
    }

    free(str);
   
    return 1;
}
