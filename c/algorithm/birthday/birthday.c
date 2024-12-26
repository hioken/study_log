// // 今年の誕生日の曜日を、今日の曜日から求める
// (今日 - 今年の誕生日) % 7 = 誕生日との曜日差
// 曜日[ (曜日差 + 今日の曜日のインデックス番号) % 7 ]

// // 今年の誕生日の曜日を、元旦の曜日から求める
// 今書いてる事

// // 今年のx日の曜日と、誕生歳のx日の曜日差
// 今日の曜日 - (今年 - 誕生年 + a) = 誕生年の今日の曜日
// (今年 - 誕生日) / 4 = a(うるう年)

// // 元旦の計算
日付差 + 3 = その年の曜日

// 日付計算
// 日数[月] - 誕生日の日付

#include <stdio.h>

char week_day[7][12] = {"日曜日", "月曜日", "火曜日", "水曜日", "木曜日", "金曜日", "土曜日"};
int days[12] = {31 ,59 ,90 ,120 ,151 ,181 ,212 ,243 ,273 ,304 ,334 ,365};

// int whats_this_year_birthday(int target_month, int target_day, int this_year, int this_month, int today);
// int whats_year_of_birth(target, this_year);

// int whats_this_year_birthday(int target_month, int target_day, int this_year, int this_month, int today) {
//   (today - target)

//   return
// }

int birth_of_year_day(int day);

int birth_of_year_day(int days, int this_year) {
  // 元旦の曜日
  int new_years_day;
  new_years_day = (this_year % 7) + (this_year / 4 % 7) + 4;
  // 指定の日の曜日
  return days % 7 + new_years_day;

}

void main(void) {
  int year, month, day, total_day;
  scanf("%d %d %d", &year, &month, &day);
  total_day = day;
  if(manth != 1) total_day += days[manth - 2];

  birthday = birth_of_year_day(total_day, year);

  printf("あなたの生まれた日 %d年 %d月 %d日の曜日は...%sです", year, manth, day, week_day[birthday])
}
