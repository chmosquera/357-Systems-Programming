#include <stdio.h>
#include "swap.h"
#include "checkit.h"

void test_swap(){
    int a = 5, b = 10;
    int a1 = a, b1 = b;
    swap(&a1, &b1);
    checkit_int(a == b1, 1);
    checkit_int(b == a1, 1);
}

void test_swap_1() {
    int a = 1, b = -1;
    int a1 = a, b1 = b;
    swap(&a1, &b1);
    checkit_int(a == b1, 1);
    checkit_int(b == a1, 1);
}

int main() {
    
    test_swap();
    test_swap_1();

    return 1;
}
