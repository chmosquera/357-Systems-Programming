#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void SigHandler(int signo);

int main(int argc, char ** argv) {
    char c[100];

    while (1) {
    
        fgets(c, 100, stdin);

        if (c[0] == 'q' && c[1] == 'u' && c[2] == 'i' && c[3] == 't') {
            return 1;
        }
            if (signal(SIGINT, SigHandler) == SIG_ERR) {
                fprintf(stderr, "Can't catch SIGINT\n");
            }

    }
    

    return 0;

}

void SigHandler(int signo) {

    if (signo == SIGINT) {
        printf("Enter 'quit' to terminate.\n");
    }   
}
