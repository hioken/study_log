#include <stdio.h>
#define SIZE 5

void main(void) {
    int data[SIZE] = {213,53,235,643,1};
    int max;
    max = data[0];
    
    for (int comparison = 1; comparison < SIZE; comparison++) {
        if (max < data[comparison]) {
            max = data[comparison];
        }
    }
    
    printf("%d\n", max);
}