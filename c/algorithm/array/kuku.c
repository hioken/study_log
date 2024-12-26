#include <stdio.h>

int kuku[9][9];

int main(void) {
  for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
      kuku[10-i][10-j] = i * j;
    }
  }
  
  for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
      printf("%2d", kuku[i][j]);
      if (j != 9) {
        printf(", ");
      } else {
        printf("\n");
      }
    }
    
  }
  return 0;
}
