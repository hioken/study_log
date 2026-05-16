#include <stdio.h>

typedef struct {
  int argc;
  char** argv;
  int c;
} CommandLine;

int handle_a(CommandLine* args) {
  if (args->c >= args->argc) {
    printf("CommandLine error\n");
    return 1;
  }
  printf("オプションA 引数: %s\n", args->argv[(args->c)++]);
  return 0;
}

int handle_b(CommandLine* args) {
  if (args->c >= args->argc) {
    printf("CommandLine error\n");
    return 1;
  }
  FILE *fp = fopen(args->argv[(args->c)++], "r");
  char buf[1024];

  if (fp == NULL) {
    printf("Undefined File\n");
    return 1;
  }

  printf("ファイルの中身\n");
  while (fgets(buf, sizeof(buf), fp) != NULL) {
    printf("%s", buf);
  }
  printf("\n");
  fclose(fp);
  return 0;
}

int main(int argc, char* argv[]) {

  CommandLine args = {argc, argv, 1};

  while (args.c < args.argc) {
    if (argv[args.c][0] == '-') {
      switch (argv[(args.c)++][1]) {
        case 'a':
          if (handle_a(&args)) return 1;
          break;
        case 'b':
          if (handle_b(&args)) return 1;
          break;
        default:
          printf("Undefined Option\n");
          return 1;
      }
    } else {
      printf("CommandLine error\n");
      return 1;
    }
  }

  return 0;
}