#include <stdio.h>

int sum(int min,int max)
{
	int num;
	num = (min + max) * (max - min + 1) / 2;
	return num;
}

void main(void) {
  int value;
  value = sum(50,100);
  printf("%d\n", value);
}
