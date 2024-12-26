// #include <stdio.h>

// int byte(void) {
//   int bit = 0;
//   scanf("%d", &bit);

//   if (bit < 0) byte();

//   if (bit % 8 == 0) {
//     bit = bit / 8;
//   } else {
//     bit = bit / 8 + 1;
//   }

//   return bit;
// }

// void main(void) {
//   printf("%dbyte\n", byte());
// }

/*
〇do while文
do {
  処理;
} while (条件);
これで、条件がtrueならdo ~ の処理をもう一度実行する
後判定のループ処理
for whileと違い、必ず一回は実行されるため、ミスがあった際に再入力させるのに使える
*/

#include <stdio.h>

void main(void) {
  int bit = 0;
  printf("正のbit数を入力してください。\n");
  do {
    scanf("%d", &bit);
    if (bit < 0) printf("負の値は計算できません。もう一度入力してください\n");
  } while (bit < 0);

  if (bit % 8 == 0) {
    bit = bit / 8;
  } else {
    bit = bit / 8 + 1;
  }

   printf("%dbyte\n", bit);
}
