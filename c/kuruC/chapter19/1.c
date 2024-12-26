〇動的な配列の確保
・malloc関数を仕様する事で、サイズが動的な配列を作成出来る
・引数にサイズを指定すると、そのサイズの配列を作成し、戻り値として先頭のアドレスが返ってくる
*pointer = malloc(size);
・動的に確保された、長期的に保存されるサイズの大きいメモリをヒープと呼ぶ
・ヒープに確保された配列を動的配列と呼ぶ
・ヒープはプログラム終了時まで生き残る
・注意点が3点
1.使い終わったら必ずfreeで確保したメモリを開放しないと、メモリリークの原因となる
2.メモリが確保出来なかった時(NULLが返ってきた時)は、メモリがパンクしないようにプログラムを終了させる事
3.トラブルで、確保されたメモリが他のプログラムに使われることがあるらしいので、多用は厳禁

#include <stdio.h>
#include <stdlib.h>

void main(void) {
  // 宣言と入力
  int data_count;
  int *heap;
  scanf("%d", &data_count);

  // メモリの確保、形式的にvoid *型をint *型にキャスト変換してる
  heap = (int *)malloc(sizeof(int) * data_count);

  // メモリが確保できなかったら、強制終了
  if (heap == NULL) exit(0);

  // 確保されているかの確認
  for (int i = 0; i < data_count; i++) {
    heap[i] = i + 1;
  }
  for (int i = 0; i < data_count; i++) {
    printf("%d\n", heap[i]);
  }

  // 必ずメモリを開放する
  free(heap);
}


〇配列サイズの変更
・realloc関数で配列のサイズ変更が可能
・reallocはフラグメンテーションの原因となりうるので、多用は厳禁
ポインタ = (前のポインタ, サイズ);
int *heap
int array[10];
heap = array;
heap = (int *) realloc(heap,sizeof(int) * 200);
