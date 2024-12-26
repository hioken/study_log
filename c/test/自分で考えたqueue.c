#include <stdio.h>

#define N 10
typedef int data_t;

data_t queue[N];
int head;
int tail;

void init(void)
{
    head = 0;
    tail = 0;
}

void enqueue(data_t x)
{
    if (tail >= N) {
        printf("queue overflow\n");
        return;
    }

    queue[tail] = x;
    tail++;
}

void dequeue(data_t *x)
{
    if (head == tail) {
        printf("queue underflow\n");
        return;
    }

    *x = queue[head];

    for (int i = 0; i < tail - head; i++) {
        queue[head + i] = queue[head + 1 + i];
    }
    tail--;
}

int main(void)
{
    // キューの初期化
    init();

    // キューに値を追加
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    // キューから値を取り出す
    int x;
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);

    // 二巡目追加
    enqueue(50);
    enqueue(60);
    enqueue(70);
    enqueue(80);
    enqueue(50);
    enqueue(60);
    enqueue(70);
    enqueue(80);

    // 二巡目取り出し
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
    dequeue(&x);
    printf("%d\n", x);
}
