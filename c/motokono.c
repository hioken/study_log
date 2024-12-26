#include <stdio.h>

void girl_friend(int count, int girls) {
  if (count + 1 == girls) {
    printf("元×%dカノに元×%dカノの話をしたらフラれた\n", count, girls);
  } else {
    girl_friend(count + 1, girls);
    printf("って話を元×%dカノにしたらフラれた\n", count);
  }
}

int main(void) {
  int girls;
  scanf("%d", &girls);
  girl_friend(1, girls);
  return 0;
}