#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

char ** getcmd(char *, char *);

int main(int argc, char ** argv) {
    pid_t pid;
    FILE * file;
    char ** cmd;
    int status;
    int newfd;

    if (argc < 3) {
        printf("required files: [program name]\t[file name]\n");
        exit(0);
    }

    /* open file, redrirect results to file */
    if ((newfd = open(argv[2], O_WRONLY| O_TRUNC | O_CREAT , S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) < 0) printf("could not open file descriptor");
    if (dup2(newfd, 1) < 0) printf("error dup2");


    char ** c;
    c[0] = argv[1];
    c[1] = NULL;

    if ((pid = fork()) < 0) {
        printf("error\n");
    } else if(pid == 0) {
        printf("chidproc\n");
        execl(argv[1], argv[1], NULL);
        printf("failed\n");
        _exit(0);
    } else {
        printf("parent\n");
        while(waitpid(pid, &status, 0) < 0);
    }

    close(newfd);
    return 0;

}

char ** getcmd(char * program, char * file) {
    char ** command = (char **)malloc(sizeof(char *) * 3);

    command[0] = program;
    command[1] = ">";
    command[2] = file;

    return command;
}
