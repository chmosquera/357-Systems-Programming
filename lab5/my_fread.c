#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define bytes 2048

void freadProg(int argc, char * str) {
    FILE * file;
    char * buf = (char *)malloc(sizeof(char) * bytes);

    printf("BYTES: %d\n", bytes);

    file = fopen(str, "r");

    while(fread(buf, sizeof(char), bytes, file) > 0) {
        
    }
}
int main(int argc, char **argv) {

    char * file = "/usr/lib/locale/locale-archive";
    freadProg(argc, file); 
    return 1;
}

