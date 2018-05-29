#include <stdio.h>

#include "checkit.h"
#include "part3.h"

int list1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void test_sum(){
   #define NUM_OF_ELEMENTS 10
   checkit_int(sum(list1, NUM_OF_ELEMENTS), 45);
   #undef NUM_OF_ELEMENTS
}

void test_sum_1(){
   #define NUM_OF_ELEMENTS 0
   checkit_int(sum(list1, NUM_OF_ELEMENTS), 0);
   #undef NUM_OF_ELEMENTS
}

void test_sum_2(){
   #define NUM_OF_ELEMENTS 20
   checkit_int(sum(list1, NUM_OF_ELEMENTS), 45);
   #undef NUM_OF_ELEMENTS
}

void test_sum_3(){
   #define NUM_OF_ELEMENTS -1
   checkit_int(sum(list1, NUM_OF_ELEMENTS), 0);
   #undef NUM_OF_ELEMENTS
}

int main() {
   test_sum();
   test_sum_1();
   test_sum_2();
   test_sum_3();   
   return 0;
}
