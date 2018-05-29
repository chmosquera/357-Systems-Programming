
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    int s_int, i = 0;
    char *p;

    if (argc < 2) {
        printf("int required");
        exit(0);
    }

    s_int = (int)strtol(argv[1], &p, 10);

    while (i <= s_int) {
        if ((i%2) == 0){
            printf("%d\n", i);
        }
        ++i;
    }
    return 0;
}

