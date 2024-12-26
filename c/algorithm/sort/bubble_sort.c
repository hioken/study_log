#include <stdio.h>
#define SIZE 5

int debug = 0;

void main(void) {
  int data[SIZE] = {4,24,50,4030,242};
  for (int i = 0, last = 0; i < SIZE && last == 0; i++) {
    for (int j = 0; j < SIZE - i - 1; j++) {
      if (data[j] > data[j + 1]) {
        int buf = data[j];
        data[j] = data[j + 1];
        data[j + 1] = buf;
        last++;
      }
    }
    debug++;
  }
  
  for (int i = 0; i < SIZE; i++) {
    printf("%d\n", data[i]);
  }
  printf("debug : %d\n", debug);
}

