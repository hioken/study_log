#include <stdio.h>
#include <time.h>
#define MONTH 12

typedef struct {
  int days;
  int total;
} Month_data;

void main(void) {

  int b_year, b_month, b_day, progress = 1;

  time_t t = time(NULL);
  localtime_r(&t, &tm);

  int data[MONTH] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  Month_data months[MONTH] = {{0,31}};

  for (int i = 0; i < MONTH; i++) {
    months[i].days = data[i];
    if(i > 0) months[i].total = data[i] + months[i - 1].total;
  }

  free(data);

// for (int i = 0; i < MONTH; i++) {
// printf("%d月 days : %d total : %d\n", i + 1, months[i].days, months[i].total);
// }

// 〇1
//   4で割った数 + (100で割り切れる数 * 3/4)
//   1900の2月以前なら-1

// 〇2
//   1900年からの合計日数を誕生日と今で算出して差分をだす

// 〇3
//   誕生日の1990年からの経過日数(a)と、2100年から現在までの日数(b)を取得
//   1900年から2100年の日数 - a - b = 経過日数

  // 入力
  printf("生年月日を以下の通りに入力してください。\n西暦 月 日\n");
  scanf("%d %d %d", &b_year, &b_month, &b_day);


// 生まれてから%4 誕生日%4=0,1,2,3
// 0 1, 0, 0, 0
// 1 1, 0, 0, 1
// 2 1, 0, 1, 1
// 3 1, 1, 1, 1

// 誕生日%4 生まれてから%4
// 0 1, 1, 1, 1 0, 1, 2, 3
// 1 0, 0, 0, 1 1, 2, 3, 0
// 2 0, 0, 1, 1 2, 3, 0, 1
// 3 0, 1, 1, 1

// a = 今の年数 - 誕生年数
// total_uru = a/4 + 1
// if (誕生%4 != 0 && 誕生%4 + a%4 < 4) total_uru -= 1;
// if (誕生 == 1900 && 誕生月 <= 2) total_uru += 1;

  0 4 8 12
  200x = 200y
}


  0 4 8 12
  200x = 200y
}
