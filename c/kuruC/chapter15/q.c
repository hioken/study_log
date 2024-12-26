// #include <stdio.h>

// void maxmin(int array[], int *max, int *min, int size);

// void maxmin(int array[], int *max,int *min, int size) {
//   for (int i = 0; i < size; i++) {
//     printf("%2d, ", array[i]);
//   }
//   printf("\n\n");

//   for (int i = 0; i < size; i++) {
//     if (array[i] > *max) {
//       *max = array[i];
//     } else if (array[i] < *min) {
//       *min = array[i];
//     }
//   }
// }

// int main(void) {
//   int suuti[10];
//   int max = 0, min = 0;

//   printf("数値を10つまで入力してください、-1を入力すると入力が終了します\n");
//   for (int i = 0; i < 10; i++) {
//     scanf("%d", &suuti[i]);
//     if (suuti[i] == -1 && i == 0) {
//       printf("数値を一つ以上入力してください\n");
//       return 0;
//     } else if (suuti[i] == -1) {
//       i = 11;
//     }
//   }

//   maxmin(suuti, &max, &min, sizeof(suuti) / sizeof(suuti[0]));

//   printf("最大 : %d\n最小 : %d\n", max, min);
//   return 0;
// }

#include <stdio.h>

void maxmin(int array[], int *max, int *min, int size);

void maxmin(int array[], int *max,int *min, int size) {
  // デバッグ用、入力数値の確認
  for (int i = 0; i < size; i++) {
    printf("%2d, ", array[i]);
  }
  printf("\n\n");

  // maxとminの初期化
  *max = *min = array[0];

  // maxとminを求める
  for (int i = 1; i < size; i++) {
    if (array[i] > *max) {
      *max = array[i];
    } else if (array[i] < *min) {
      *min = array[i];
    }
  }
}

int main(void) {
  // 宣言
  int suuti[10];
  int max = 0, min = 0, size = 0;

  // 入力
  printf("数値を10つまで入力してください、-1を入力すると入力が終了します\n");
  for (int i = 0; i < 10; i++) {
    scanf("%d", &suuti[i]);
    if (suuti[i] == -1 && i == 0) {
      printf("数値を一つ以上入力してください\n");
      return 0;
    } else if (suuti[i] == -1) {
      size--;
      i = 11;
    }
    size++;
  }

  // maxとminを求める関数を呼び出し
  maxmin(suuti, &max, &min, size);

  // 結果の出力
  printf("最大 : %d\n最小 : %d\n", max, min);
  return 0;
}


*p == p
