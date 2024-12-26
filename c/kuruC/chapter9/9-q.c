#include <stdio.h>

void main(void) {
  for (int i = 1; i < 10; i++) {
    for (int j = 1; j < 10; j++) {
      printf("%d * %d = %3d\n", i, j, i * j);
    }
  }
}
