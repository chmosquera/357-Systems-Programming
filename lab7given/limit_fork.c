#include "limit_fork.h"
#include <sys/resource.h>
#include <stdlib.h>

void limit_fork(rlim_t max_procs)
{
   struct rlimit rl;

   if (getrlimit(RLIMIT_NPROC, &rl))
   {
      perror("getrlimit");
      exit(-1);
   }

   rl.rlim_cur = max_procs;

   if (setrlimit(RLIMIT_NPROC, &rl))
   {
      perror("setrlimit");
      exit(-1);
   }
}

int main(void) {
    limit_fork(10);
    /* continue with program logiv here */



    return 0;

}
