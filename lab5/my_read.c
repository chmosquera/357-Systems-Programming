#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define bytes 2048

void readProg(int argc, char * str) {
    int fd;
    char * buf = (char *)malloc(sizeof(char) * bytes);

    printf("BYTES: %d\n", bytes);

    fd = open(str, O_RDONLY);

    while (read(fd,buf,bytes) > 0) {
    }
}
int main(int argc, char **argv) {

    char * file = "/usr/lib/locale/locale-archive";
    readProg(argc, file);
    return 1;
}

