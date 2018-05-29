#include <stdio.h>

#include "checkit.h"
#include "part2.h"

void test_calc_1()
{
   checkit_double(calc(-1.0), 40);
}

void test_calc()
{
   test_calc_1();
}

void test_calc_2(){
  checkit_double(calc(2.5),42.5641);
}
 
void test_calc_3() {
   checkit_double(calc(2.0), 42.20498);
}

int main(void)
{
   test_calc();
   test_calc_2();
   test_calc_3();
   
   return 0;
}

