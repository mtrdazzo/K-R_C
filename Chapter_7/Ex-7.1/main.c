/*
 * Ex 7-1
 *
 * Write a program that converts upper case to lower and lower case to upper,
 * depending on the name it is invoked with, as found in argv[0].
 *
 *
 * Usage:
 *
 * upper
 *    User input is output as uppercase.
 *
 * lowercase
 *    User input is output as lowercase.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Ex_7_1.h"

int main(int argc, char **argv)
{
  int c;
  bool (*comp)(int);
  int (*covert)(int);

  if (strcmp(*argv, "./lower") == 0) {
    comp = &is_upper;
    covert = &to_lower;
  }
  else if (strcmp(*argv, "./upper") == 0) {
    comp = &is_lower;
    covert = &to_upper;
  }
  else
    return -1;

  while ((c = getchar()) != EOF) {
    if ((*comp)(c))
      putchar((*covert)(c));
    else
      putchar(c);
  }

  return 0;
}
