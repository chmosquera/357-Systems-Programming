#include <stdio.h>

#include "part3.h"

int sum(int list[], int length) {
   int y = 0;
   int i;
   for (i = 0; i < length; i++) {
      y = y + list[i];
   }
   
   return y;
}

