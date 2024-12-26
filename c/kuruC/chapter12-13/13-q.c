#include <stdio.h>

void main(void) {
  int array[5];
  printf("整数5つ入力してください\n");
  for (int i = 0; i < 5; i++) {
    scanf("%d", &array[i]);
  }

  for (int i = 4; i >= 0; i--) {
    printf("array[%d] : %d\n", i, array[i]);
  }
}
