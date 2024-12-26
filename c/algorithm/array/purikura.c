#include <stdio.h>
#define HEIGHT 9
#define WIDTH 9

int data[HEIGHT][WIDTH] = {
  {0,0,0,1,1,1,1,1,1},
  {0,0,0,1,1,1,1,1,1},
  {0,0,0,1,1,1,1,1,1},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0,0},
  {1,1,1,1,1,1,0,0,0},
  {1,1,1,1,1,1,0,0,0},
  {1,1,1,1,1,1,0,0,0}
};

int upload[9][9];

int main(void) {
  int mini_height = HEIGHT / 3;
  int mini_width = WIDTH / 3;
  int mini_tate, mini_yoko;
  int count = 1;

  for (int tate = 0; tate < HEIGHT - 1; tate = tate + 3) {
    for (int yoko = 0; yoko < WIDTH - 1; yoko = yoko + 3) {
      for (int i = 0; i < mini_height; i++) {
        for (int j = 0; j < mini_width; j++) {
          mini_tate = mini_height * i + tate / 3;
          mini_yoko = mini_width * j + yoko / 3;
          upload[mini_tate][mini_yoko] = data[tate][yoko];
          if (count != 1000) printf("%3d: up[%d][%d] <= data[%d][%d]\n", count, mini_tate, mini_yoko, tate, yoko);// debug
          count++; // debug
        }
      }
    }
  }
  
  printf("data[0][3] : %d\n", data[0][3]);
  printf("up[0][1] : %d\n", upload[0][1]);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%s", upload[i][j] == 1 ? "●" : " ");
    }
    printf("\n");
  }
  
  return 0;
}
