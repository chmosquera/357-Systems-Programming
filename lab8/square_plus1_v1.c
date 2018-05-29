#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_SIZE 265

void pipeitup(char * num);

int main (int argc, char ** argv) {
    int n; char buf[BUF_SIZE];

    /* read from stdin until EOF */
    do {
        read(STDIN_FILENO, buf, BUF_SIZE);
 /*       n = strtol(buf, NULL, 10); */
        printf("buf: %s\n", buf);
        pipeitup(buf);
        buf[0] = '\0';
    } while (*buf != EOF);

    return 1;
}
 
void pipeitup(char * num) {
    pid_t pid1, pid2;
    int fd1[2], fd2[2], fd3[2]; 
    int n; char buf[BUF_SIZE];

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

    if (pid1 < 0) {
        fprintf(stderr, "fork 1 error\n");
        exit(errno);
    } else if (pid1 > 0) {    /* parent - reads initial number and prints final number */
        printf("entered the parent proc\n")

        /* write initial number - n - to pipe1 */
        write(fd1[0], num, BUF_SIZE);

        /* wait for children - robust*/
        if (wait(NULL) < 0) {
            fprintf(stderr, "error waiting \n");
            exit(-1);
        }   
        if (wait(NULL) < 0) {
            fprintf(stderr, "error waiting \n");
            exit(-1);
        }   

        /* read final output and print it */
        read(fd3[0], buf, BUF_SIZE);
        n = strtol(buf, NULL, 10);
        fprintf(stdout, "final int: %d\n", n);

        /* close all of pipes file descriptors */
        if (close(fd1[0]) < 0) {
            exit(errno);
        }
        if (close(fd1[1]) < 0) {
            exit(errno);
        }
        if (close(fd2[0]) < 0) {
            exit(errno);
        }
        if (close(fd2[1]) < 0) {
            exit(errno);
        }
        if (close(fd3[0]) < 0) {
            exit(errno);
        }
        if (close(fd3[1]) < 0) {
            exit(errno);
        }
        printf("closed all the fds from the parent\n");

    } else {                /* child 1 - square number */
        printf("entered child 1\n");

        close(fd1[1]);      /* close pipe1 write end */
        close(fd2[0]);      /* close pipe2 read end */
        close(fd3[0]);      /* don't need to use pipe 3 */
        close(fd3[1]);  
        printf("closed the fds in child 1\n");

       /* if (read(fd1[0], buf, 1) < 0) {  */      /* read int from pipe1 */
        /*    printf("error reading\n");
        } */
        scanf("%d", &n);
        printf("yo\n");
        printf("buf: %s\n", buf);
        n =  strtol(buf, NULL, 10);         /* convert char * to an int */
        printf("n = %d\n", n);
        n = n * n;                          /* square the number */
        close(fd1[0]);

        write(fd2[1], &n, sizeof(n));       /* write squared value to pipe 2 */
        close(fd2[1]);
        
        /* Fork process again */
        if ((pid2 = fork()) < 0) {
            fprintf(stderr, "fork 1 error\n");
            exit(errno);
        } else if (pid2 == 0) {          /* child 2 - add 1 to number */
            printf("entered child 2\n");

            close(fd1[0]);           
            close(fd1[1]);           
            close(fd2[1]);
            close(fd3[0]);

            read(fd2[0], buf, BUF_SIZE);        /* read int from pip 2 */
            n = strtol(buf, NULL, 10);
            n += 1;
            close(fd2[0]);

            write(fd3[1], &n, sizeof(n));
            close(fd3[1]);

        }



    }


}
