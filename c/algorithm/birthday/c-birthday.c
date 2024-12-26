未完成、うるう年の計算と15行目の最後に足している数がずれている
#include <stdio.h>

char week_day[7][12] = {"日曜日", "月曜日", "火曜日", "水曜日", "木曜日", "金曜日", "土曜日"};
int days[12] = {0, 31 ,59 ,90 ,120 ,151 ,181 ,212 ,243 ,273 ,304 ,334};

int birth_of_year_day(int days, int this_year);



int birth_of_year_day(int days, int this_year) {
  // 元旦の曜日、後でまとめて計算するため % 7しない
  int new_years_day;
  new_years_day = this_year + this_year / 4 + 2;
  // 指定の日の曜日
  // 日数経過による曜日のズレ - 1で元旦に合わせる
  return (days + new_years_day) % 7;
}


void main(void) {
  int year, month, day, total_day, birthday;
  printf("生年月日を以下の通りに入力してください\n西暦 月 日にち\n");
  scanf("%d %d %d", &year, &month, &day);
  // 元日から何日経ったか計算
  total_day += days[month - 1] + day;

  birthday = birth_of_year_day(total_day, year);

  printf("\nあなたの生まれた日 %d年 %d月 %d日の曜日は...%sです\n", year, month, day, week_day[birthday]);
}
