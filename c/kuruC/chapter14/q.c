#include <stdio.h>
#include <string.h>

void main(void) {
  char f_name[100];
  char l_name[100];
  scanf("%s", f_name);
  scanf("%s", l_name);
  printf("%s\n", strcat(f_name, l_name));
  printf("%s\n", f_name);
  printf("%s\n", l_name);
}
