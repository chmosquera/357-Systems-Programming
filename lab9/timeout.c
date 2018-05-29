#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void Execute();
void SignalHandler(int);
void SigActSetup();
pid_t pid;

int main(int argc, char ** argv) {


    if (argc < 3) {
        printf("Usage: %s\t<int>\t<command\n", argv[0]);
        exit(-1);
    }

/*    alarm(1);
    while (1) {

    } */

    Execute(argv);

    return 1;

}

void SigActSetup() {
    struct sigaction new_sa;

    /* setup new action */
    new_sa.sa_handler = SignalHandler;
    new_sa.sa_flags = 0;

    /* modifies the given signal with the given sigaction */
    sigaction(SIGALRM, &new_sa, NULL); 
    sigaction(SIGCHLD, &new_sa, NULL);  

}
void Execute(char ** argv) {
    pid_t pid;
    int status = 0, i;

    i = atoi(argv[1]);

    if ((pid = fork()) < 0) {

    } else if (pid == 0) {
        execvp(argv[2], argv + 2); 
        exit(status);
    } else {
        alarm(i);
        while (waitpid(pid, &status, 0) < 0){}
    }

}

void SignalHandler(int signo) {

    if (signo == SIGALRM) {
        printf("recieved alarm signal\n");
        kill(pid, 0);
        exit(1);
    }
    else if (signo == SIGCHLD) {
        printf("recieved child signal\n");
        exit(pid);
    }
    
}

