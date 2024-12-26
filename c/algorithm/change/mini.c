#include <stdio.h>

int change(int *money, int *unit, int bill_coin[][2]);

void main(void) {
  int  money, count, unit = 0;
  // テストデータ
  int bill_coin[9][2] = {{10000,1}, {5000,20}, {1000,20}, {500,20}, {100,20}, {50,0}, {10,20}, {5,0}, {1,20}};
  // 金額入力
  scanf("%d", &money);

  while (unit < 9) {
    count = change(&money, &unit, bill_coin);
    printf("%5d円 : ", bill_coin[unit - 1][0]);
    if (count != 0 && bill_coin[unit - 1][1] == 0) {
      printf("%d枚...お釣りが切れました\n", count);
    } else if (count != 0) {
      printf("%d枚\n", count);
    } else if (count == 0 && money >= bill_coin[unit - 1][0]) {
      printf("釣銭切れ\n");
    } else {
      printf("0枚\n");
    }
  }
}

int change(int *money, int *unit, int bill_coin[][2]) {
  int count;

  count = *money / bill_coin[*unit][0];
  if (count > bill_coin[*unit][1]) {
    count = bill_coin[*unit][1];
  }

  *money -= count * bill_coin[*unit][0];
  bill_coin[*unit][1] -= count;

  *unit += 1;

  return count;
}
