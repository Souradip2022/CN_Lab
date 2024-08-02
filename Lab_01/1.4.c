#include <stdio.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
} a;

int main() {

  unsigned int n;
  printf("Enter a number: ");
  scanf(" %d", &n);
  a.ch1 = n & 0xFF;
  a.ch2[0] = (n >> 8) & 0xFF;
  a.ch2[1] = (n >> 16) & 0xFF;
  a.ch3 = (n >> 24) & 0xFF;

  printf("ch1: %d\nch2: %d, %d\nch3 %d\n", a.ch1, a.ch2[0], a.ch2[1], a.ch3);

  return 0;
}