#include <stdio.h>

#define ARRAY_SIZE 4 /* size of array */

typedef struct {
    int id;
    char name[20];
    int attack;
} Weapon;

int main(void)
{
    Weapon a[ARRAY_SIZE] = {{1, "dragon", 30}, {2, "goust", 12}, {3, "fire", 20}, {4, "nomal", 10}}; /* sorted array */
    int left = 0; /* start key of index */
    int right = ARRAY_SIZE; /* end key of index */
    int mid; /* middle key of index */
    int value; /* search value */
    Weapon *target;

    puts("Find value?");
    scanf("%d", &value);

    while(left <= right) {
        mid = (left + right) / 2; /* calc of middle key */
        if (a[mid].id == value) {
            puts("Found!\n");
            // ループの後でデータを操作できるように、ポインタを移動
            target = &a[mid];
            printf("%d\n%s\n%d\n", target->id, target->name, target->attack);
            return 0;
        } else if (a[mid].id < value) {
            left = mid + 1; /* adjustment of left(start) key */
        } else {
            right = mid - 1; /* adjustment of right(end) key */
        }
    }
    puts("Not Found.\n");
    return 0;
}
