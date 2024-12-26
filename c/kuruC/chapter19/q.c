#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char name[10];
  int age;
  char gender[10];
} Student;

void student_print(Student student[]);
void student_input(Student student[]);

int datasize = 10;

void main(void) {
  Student *array;

  array = malloc(sizeof(Student) * datasize);

  student_input(array);
  student_print(array);

  free(array);
}

void student_print(Student student[]) {
  for (int i = 0; i < datasize; i++) {
    printf("name: %s, age: %d, gender: %s\n", student[i].name, student[i].age, student[i].gender);
  }
}

void student_input(Student student[]) {
  for (int i = 0;; i++) {
    printf("%d人目の名前を入力してください\n", i + 1);
    scanf("%S", &student[i].name);
    printf("%d人目の年齢を入力してください\n", i + 1);
    scanf("%d", &student[i].age);
    if (student[i].age == -1) break;
    printf("%d人目の性別を入力してください(man または woman)\n", i + 1);
    scanf("%s", &student[i].gender);

    if (i + 1 == datasize) {
      datasize += 10;
      student = realloc(student, sizeof(Student) * datasize);
      if (student == NULL) exit(0);
    }
  }
}
