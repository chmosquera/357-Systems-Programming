#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void Exec_print(int s_int);

int main(int argc, char ** argv) {
    int s_int;
    char *p;

    if (argc < 2) {
        printf("single integer required\n");
        exit(0);
    }

    
    s_int = (int)strtol(argv[1], &p, 10 );
    printf("argv[1] : %d\n\n", s_int);

    Exec_print(s_int);

    
    return 0;

}

void Exec_print(int s_int) {
    pid_t pid = NULL;
    int i = 0, status;

    pid = fork();

    if (pid < 0) {
        exit(-1);
    } else if (pid == 0) {
        while (i < s_int) {
            if ((i%2) == 1) {
                printf("%d\n", i);
            }
            ++i;
        }
        _exit(0);
    } else if (pid > 0) {
        while (i < s_int) {
            if ((i%2) == 0) {
                printf("\t%d\n", i);
            }
            ++i;
        }
        while (waitpid(pid, &status, 0) < 0 ) {
            /* Returns the pid of the child process that terminated
             * if child process hasn't terminated, it'll keep waiting */
        }
    }


}
