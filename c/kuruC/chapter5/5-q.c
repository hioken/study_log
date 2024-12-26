#include <stdio.h>

void main(void)
{
  int money, juice, milk, change;
  juice = 198;
  milk = 138;
  money = 1000;

  change = money - (int)((juice + milk * 2) * 1.05);
printf("%d\n", change);
}
