// 実装ならず
#include <stdio.h>

#define N 20

typedef int data_t;

data_t queue[N];
int head = 0;
int tail = 0;;

void enqueue(x) {
    queue[tail] = x;
    tail++;
}

void dequeue(data_t *x) {
    *x = queue[head];
    head++;
}

int main(void)
{
    enqueue(10);
    enqueue(20);

    data_t *p;

    dequeue(&p);
    printf("%d\n", *p);
}
