#include <stdio.h>

int main() {
  int i = 1;
  char *c = (char *) &i;
  int *pi = &i;
  printf("%ld\n", sizeof *c);
  printf("%ld\n", sizeof *pi); //1
  printf("%d\n", c[0]); //1
  printf("%d\n", c[1]); //0
  if (c[0]) {
    printf("Little Endian");
  } else {
    printf("Big Endian");
  }

  return 0;}