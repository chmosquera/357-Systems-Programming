#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char ** argv) {

    long childmax, open_max, page_size;

    childmax = sysconf(_SC_CHILD_MAX);
    printf("child_max: %lu\n", childmax);

    open_max = sysconf(_SC_OPEN_MAX);
    printf("open_max: %lu\n", open_max);

    page_size = sysconf(_SC_PAGESIZE);
    printf("page_sizeL %lu\n", page_size);

    return 1;
}
