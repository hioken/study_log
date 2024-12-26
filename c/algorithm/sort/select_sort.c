#include <stdio.h>
#define SIZE 5

void main(void) {
    int data[SIZE][1] = {{430},{943},{39},{3},{348}};
    int min;
    
    
    
    for (int i = 0; i < SIZE - 1; i++) {
      min = i;
      for (int comparison = i + 1; comparison < SIZE; comparison++) {
          if (data[min][0] > data[comparison][0]) {
              min = comparison;
          }
      }
      if (i != min) {
        int buf = data[i][0];
        data[i][0] = data[min][0];
        data[min][0] = buf;
      }
    }  
    
    for (int i = 0; i < SIZE; i++) {
      printf("%d\n", data[i][0]);
    }
    
}