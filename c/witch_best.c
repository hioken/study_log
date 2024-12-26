int data[x][y];

〇パターン1
int y = 0;
int x = 0;

for (int i = 1; i < 10; i++) {
    data[y][x] = i;
    x++;
    if (y < 2 && x >= 3) {
        y++;
        x = 0;
    }
}
↑に加えてxとyのアドレスを開放する



〇パターン2
int i = 1;

for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
        data[y][x] = i;
        i++;
    }
}
↑に加えてiのアドレスを開放する


〇パターン3
for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
        data[y][x] = y * 3 + x + 1;
    }
}
