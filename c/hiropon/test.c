// #include <stdio.h>
// #define SIZE 8

// int count = 0;
// int data[SIZE] = {34,52,652,323,12,65,69,23};

// int main(void) {
//   for (int i = 0; i < SIZE - 1; i++) {
//     count++;
//     for (int j = 1; j < SIZE - i; j++) {
//     count++;
//       if (data[j - 1] > data[j]) {
//     count++;
//         int buf = data[j - 1];
//     count++;
//         data[j - 1] = data[j];
//     count++;
//         data[j] = buf;
//     count++;
//       }
//     count++;
//     }
//     count++;
//   }
  
//   for (int i = 0; i < SIZE; i++) {
//     printf("%d, ", data[i]);
//   }
//   printf("\n");
//   printf("count : %d\n", count);
//   return 0;
// }



#include <stdio.h>
#define SIZE 8

int data[SIZE] = {34,52,652,323,12,65,69,23};

int count = 0;

int main(void) {
  for(int i = 0; i < SIZE - 1; i++) {
    count++;
    int min = i;
    count++;
    for (int j = i; j < SIZE - 1; j++) {
    count++;
      if (data[min] > data[j + 1]) min = j + 1;
    count++;
    count++;
    count++;
    }
    int buf = data[i];
    count++;
    data[i] = data[min];
    count++;
    data[min] = buf;
    count++;
    count++;
  }
  
  printf("\n");
  for (int i = 0; i < SIZE; i++) {
    printf("data[%d] : %d\n", i, data[i]);
    printf("%d\n", count);
  }
}