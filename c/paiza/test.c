#include <stdio.h>

typedef struct {
    char name[20];
    int attack;
} Enemy;

typedef struct {
    char name[20];
    int hp;
} Player;

void battle(Enemy *attacker, Player *target)
{
    printf("%sは%sを攻撃！\n%dのダメージ", attacker->name, target->name, attacker->attack);
    target->hp = target->hp - attacker->attack;
    printf("%sの残りHP : %d\n", target->name, target->hp);
}

int main(void)
{
    Enemy slime = {"スライム", 10};
    Player knight = {"騎士", 200};

    Player battle_player1 = knight;
    Enemy battle_enemy1 = slime;

    battle(&battle_enemy1, &battle_player1);
    battle(&battle_enemy1, &battle_player1);
}
