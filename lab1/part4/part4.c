#include <stdio.h>
#include <ctype.h>
#include "part4.h"

void lower(char original[], char buffer[]) {
   int index = 0;
   char c = original[index];

   while (c != '\0') {
      c = original[index];
      buffer[index] = tolower(c);
      index++;
   }

}

void str_lower_mutate(char str[]) {
   int index = 0;
   char c = str[index];
   while (c != '\0') {
      c = str[index];
      str[index] = tolower(c);
      index++;
   }
}
