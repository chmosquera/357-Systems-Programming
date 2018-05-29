#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

void pipe_exec(char **, char **);
void getcmds(int, char **, char **, char **);
char ** getcmd(char ** line, char ** endptr);

int main(int argc, char * argv[]) {
    char * prog1, * prog2, **endptr;
    char cmd1[1056], cmd2[1056];

    endptr = argv;
    getcmd(argv + 1, endptr);
    printf("endptr[0] = %s\n", *endptr );
    getcmd(endptr, endptr);

    /* fix this so it takes in command line arguments */
 //   getcmds(argc, argv, &prog1, &prog2);
 //       printf("---prog1[0] = %s\t", prog1[0]);
  //      printf("---prog2[0] = %s\n", prog2[0]);
    prog1 = "ls -l";
    prog2 = "more"; 


   // pipe_exec(&prog1, &prog2);
    return 1;
}

void pipe_exec(char ** prog1, char ** prog2) {
    pid_t pid1, pid2;
    int fd[2];

    /* create pipes */
    if (pipe(fd) < 0) exit(errno);

    /* duplicate processes */
    pid1 = fork();
    pid2 = fork();

    if ((pid1 < 0) || (pid2 < 0)) exit(-1);
    else if (pid1 == 0) {            /* child 1 closes read end */
        printf("enters child 1 proc \n");
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);         /* duplicate fd[1] */
        close(fd[1]);
/*        system(prog1);*/
        printf("prog1[0] = %s\n", prog1[0]);
        execvp(prog1[0], prog1);

    } else if (pid2 == 0) {         /* child 2 closes write end */
        printf("enters child 1 proc \n");
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
 /*       system(prog2); */
        printf("prog2[0] = %s\n", prog2[0]);
        execvp(prog2[0], prog2);
    } else {        /* parent proc */
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        wait(NULL);
        exit(1);
    }

}

/*void getcmds(int argc, char ** argv, char ** prog1, char ** prog2) {
    int i = 1, flag = 0, j = 0, k = 0;

//    prog1 = &argv[i];
//    printf("*prog1 : %s\n", *prog1);


    while (i < argc) {
        printf("argv[%d]: %s\n", i, argv[i]);
        if (strcmp(argv[i],";") == 0) {
            printf("flag triggered\n");
            flag = 1;
        }
        if (flag) {
            prog1[j] = argv[i];
            printf("prog1[%d] = %s\n", i, prog1[i]);
            ++j;
        } else {
            prog2[k] = argv[i];
            printf("prog2[%d] = %s\n", i, prog2[i]);
            ++k;
        } 
        ++i;
    }
    
}*/

// once a ; is reached, it will return the array
char ** getcmd(char ** line, char ** endptr) {
    int i = 0, argcnt = 0;

    endptr = line;
 
    // count how many arguments until ; is reached
    printf("line[0] = %s\n", line[0]);
    while (strcmp(line[i], ";") != 0) {
        ++argcnt;
        ++endptr;
        printf("%d : %s\n", argcnt, line[i]);
        ++i;
    }
    ++endptr;

    printf("next arg will begin with str: %s\n", *endptr);


    return NULL;
}

