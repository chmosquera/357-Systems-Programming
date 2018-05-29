#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void Exec_print(char  * s_int);

int main(int argc, char ** argv) {

    if (argc < 2) {
        printf("single integer required\n");
        exit(0);
    }

    Exec_print(argv[1]);

    
    return 0;

}

void Exec_print(char *s_int) {
    pid_t pid = NULL, pid2 = NULL;
    char * cmd[2];
    int status;
    cmd[1] = s_int;

    if ((pid = fork()) > 0) { /* parent */
        int status2;

        while(waitpid(pid2, &status, 0) < 0) {}

        if ((pid2 = fork()) < 0) {/* parent */
        } else if (pid2 == 0){ /* child 2 */
            cmd[0] = "odds";
            execv(cmd[0], cmd);
            _exit(0);
        } else {
            while(waitpid(pid2, &status, 0) < 0){}
        }


    } else if (pid == 0) { /* child */
        cmd[0] = "evens";
        execv(cmd[0], cmd);
        _exit(0);
    }


}
