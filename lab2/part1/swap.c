#include <stdio.h>
#include "swap.h"

void swap(int *px, int *py) {
    int temp;
    temp = *px;
    *px = *py;
    *py = temp; 
}
