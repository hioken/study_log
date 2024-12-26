#include <stdio.h>

void main(void) {
    int data[3] = {0, 1, 2};
    int *point;
    
    point = &data[1];
    
    printf("%d\n", sizeof(data));
    printf("%d\n", sizeof(point));
}