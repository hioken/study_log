#include <stdio.h>

void main(void) {
  FILE *file;
  file = fopen("17-q.csv", "w");

  fprintf(file, "\"番号\",\"名前\",\"テストの平均点\"\n");
  fprintf(file, "\"1\",\"野比のび太\",\"0\"\n");
  fprintf(file, "\"2\",\"源静香\",\"90\"\n");
  fprintf(file, "\"3\",\"剛田武\",\"40\"\n");
  fprintf(file, "\"4\",\"骨川スネ夫\",\"70\"\n");

  fclose(file);
}
