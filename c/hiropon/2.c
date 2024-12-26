#include <stdio.h>

void r(int n);
int i = 1;

int main(){
  r(4);
  return 0;
}

void r(int n){
  if(n > 0){
    r(n - 2);
    printf("%3d : %d\n", n, i++);
    r(n - 1);
  }
}


// #include <stdio.h>

// void r(int);
// int j = 0;

// int main(){
//   r(3);
//   return 0;
// }

// void r(int n){
//   j++;
//   int m = j;
//   for (int k = 0; k < m; k++) {
//     printf(" ");
//   }
//   printf("%2d:%dの再帰開始\n", m, m);
//   if(n > 0){
//   for (int k = 0; k < m; k++) {
//     printf(" ");
//   }
//     printf("%2d:r(%d)へ\n", m, n-2);
//     r(n - 2); 
//   for (int k = 0; k < m; k++) {
//     printf(" ");
//   }
//     printf("%2d:r(%d)へ\n", m, n-1);
//     r(n - 1);
//   }
//   for (int k = 0; k < m; k++) {
//     printf(" ");
//   }
//   printf("%2d:%dの再帰終了\n\n", m, m);
// }
