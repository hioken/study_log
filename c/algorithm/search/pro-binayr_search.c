#include <stdio.h>
#include <string.h>
#define SIZE 10

//テスト検索データ
int target = 23;
// テストデータ
int data[SIZE] = {4,5,8,23,25,35,39,49,50,59};


int main(void) {
    int is_this;
    
    int left = 0, right = SIZE - 1;
    
    
    while (left <= right) {
        is_this = (left + right) / 2;
        if (data[is_this] == target) {
            printf("配列の%d番目でした\n", is_this + 1);
            return 0;
        } else if (data[is_this] > target) {
            right = is_this - 1;
            printf("debug : %d\n", is_this);
        } else {
            left = is_this + 1;
            printf("debug : %d\n", is_this);
        }
    }
    
    printf("Not Finded!\n");
 
    return 0;
}
