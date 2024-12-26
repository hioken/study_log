#include <stdio.h>

void main(void) {
  // 宣言、入力
  int month;
  scanf("%d", &month);

  // 表示
  switch(month) {
    case 1:
      printf("睦月");
      break;
    case 2:
      printf("如月");
      break;
    case 3:
      printf("弥生");
      break;
    case 4:
      printf("卯月");
      break;
    default:
      printf("これ以上書きたく無かった、4月までにしてくれ");
  }
}
