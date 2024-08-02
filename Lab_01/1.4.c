#include <stdio.h>

int main() {
  int a, b, c, d;
  int variable = 0x12345678;
  a = (variable & 0xFF);
  b = ((variable >> 8) & 0xFF);
  c = ((variable >> 16) & 0xFF);
  d = ((variable >> 24) & 0xFF);

  printf("a = %02x\n", a);
  printf("b = %02x\n", b);
  printf("c = %02x\n", c);
  printf("c = %02x\n", d);

  return 0;
}