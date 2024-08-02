#include <stdio.h>

unsigned int reverse_byte_order(unsigned int num) {
  return ((num >> 24) & 0x000000FF) |
         ((num >> 8) & 0x0000FF00) |
         ((num << 8) & 0x00FF0000) |
         ((num << 24) & 0xFF000000);
}

void print_bytes(unsigned int num) {
  unsigned char *byte = (unsigned char *) &num;
  for (int i = 0; i < 4; i++) {
    printf("Byte %d: 0x%02x\n", i, byte[i]);
  }
}

int main() {
  unsigned int num = 0x1;
  char *byte = (char *) &num;
  if (byte[0] == 1) {
    printf("The system is Little Endian\n");
  } else {
    printf("The system is Big Endian\n");
  }

  unsigned num2 = 0x01020304;

  printf("Original number: 0x%x\n", num2);
  printf("Bytes of the original number:\n");
  print_bytes(num2);

  unsigned int converted_num = reverse_byte_order(num2);
  printf("Converted number: 0x%x\n", converted_num);
  printf("Bytes of the converted number:\n");
  print_bytes(converted_num);

  return 0;
}
