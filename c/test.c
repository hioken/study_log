#include <stdio.h>

int main(void) {
  int a = 0, b = 1;
  &a = &b;
  printf("aのアドレス : %p\n", &a);
  printf("aの値 : %d\n", a);
  printf("bのアドレス : %p\n", &b);
  printf("bの値 : %d\n", b);
}