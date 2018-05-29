#include <stdio.h>

#include "checkit.h"
#include "part4.h"

void test_lower() {
   char inStr[] = "DOG";
   char outStr[4];  
   lower(inStr, outStr);
   checkit_string(outStr, "dog");
}

void test_lower_1() {
   char inStr[] = " ";
   char outStr[2];  
   lower(inStr, outStr);
   checkit_string(outStr, " ");
}

void test_lower_2() {
   char inStr[] = "TabLes";
   char outStr[7];  
   lower(inStr, outStr);
   checkit_string(outStr, "tables");
}

void test_lower_mutate() {
   char str[] = "HELLO";
   str_lower_mutate(str);
   checkit_string(str, "hello");
}
void test_lower_mutate_1() {
   char str[] = "blOOp";
   str_lower_mutate(str);
   checkit_string(str, "bloop");
}

int main() {
   test_lower();
   test_lower_1();
   test_lower_2();
   test_lower_mutate();
   test_lower_mutate_1();
   return 0;
}

