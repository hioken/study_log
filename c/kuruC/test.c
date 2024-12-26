#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void) {
	char type[20];
	strcpy(type, "type");
	char str[8] = "text : ";
	strcat(str, type);
	printf("%s\n", str);
}

// #include <stdio.h>

// void main(void) {
//   FILE *file;
//   char str[50] = "ファルコン・ランチ";

//   file = fopen("test.txt", "w");
//   fprintf(file, "Hello world\n変数の内容 : %s\n", str);
//   fclose(file);
// }


// #include <stdio.h>

// int main(int argc,char *argv[])
// {
//   // for (int i = 0; argv[1][i] != '\0'; i++) {
//   //   printf("%d文字目 : %c\n", i + 1, argv[1][i]);
//   // }

//     if (argc > 1) {
//       FILE *file;
//       file = fopen(argv[1], "a");

//       if (argv[2][0] == '-') {
//         switch(argv[2][1]) {
//           case 'd':
//             fprintf(file, "%s\n", argv[3]);
//             fprintf(file, "%s\n", argv[3]);
//             break;
//           case 't':
//             fprintf(file, "%s\n", argv[3]);
//             fprintf(file, "%s\n", argv[3]);
//             fprintf(file, "%s\n", argv[3]);
//             break;
//           default:
//             printf("not command find\n");
//             return 0;
//         }
//       } else {
//         fprintf(file, "%s\n", argv[2]);
//       }
//     }

//     fflush(stdin);
//     getchar();

//     return 0;
// }
