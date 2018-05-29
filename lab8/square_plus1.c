#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char ** argv) {
    pid_t pid1, pid2;
    int fd1[2], fd2[2], fd3[2]; 
    int n; 

    /* Create all dem pipes */
    if (pipe(fd1) < 0) {
        fprintf(stderr, "pipe1 error\n");
        exit(errno);
    }
    if (pipe(fd2) < 0) {
        fprintf(stderr, "pipe2 error\n");
        exit(errno);
    }
    if (pipe(fd3) < 0) {
        fprintf(stderr, "pipe3 error\n");
        exit(errno);
    }

    /* Begin forking process */
    pid1 = fork();
    pid2 = fork();

    if ((pid1 < 0) || pid2 < 0) {
        fprintf(stderr, "fork 1 error\n");
        exit(errno);
    } else if (pid1 > 0) {    /* parent - reads initial number and prints final number */
        close(fd1[0]);
        close(fd3[1]);

        while (1) {
            char line[1024];
            read(STDIN_FILENO, line, sizeof(line));
            if (line[0] == EOF) {
                kill(pid1, SIGKILL);
                kill(pid2, SIGKILL);
                exit(-1);
            }
            n = atoi(line);         /* convert string to integer */

            write(fd1[1], &n, sizeof(n));
            read(fd3[0], &n, sizeof(n));
            printf("final int: %d\n", n);
        }

    } else if (pid2 == 0) {          /* child 2 - add 1 to number */
        close(fd2[1]);           /* close write end of pipe 2 */
        close(fd3[0]);          /* close read end of pipe 3 */

        while(1) {
            read(fd2[0], &n, sizeof(n));
            n += 1;
            write(fd3[1], &n, sizeof(n));
        }

    } else if (pid1 == 0) {                /* child 1 - square number */
        close(fd1[1]);          /* close write end of pipe 1 */
        close(fd2[0]);          /* close read end of pipe 2 */
        
        while (1) {
            read(fd1[0], &n, sizeof(n));
            n = n * n;
            write(fd2[1], &n, sizeof(n));
        }
    }

    return 0;


}
