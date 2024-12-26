#include <stdio.h>

typedef struct {
  char name[10];
  int age;
  char gender[10];
} Student;

void student_print(Student student[]);
void student_input(Student student[]);

void main(void) {
  Student array[3];

  student_input(array);
  student_print(array);
}

void student_print(Student student[]) {
  for (int i = 0; i < 3; i++) {
    printf("name: %s, age: %d, gender: %s\n", student[i].name, student[i].age, student[i].gender);
  }
}

void student_input(Student student[]) {
  for (int i = 0; i < 3; i++) {
    printf("%d人目の名前を入力してください\n", i + 1);
    scanf("%s", &student[i].name);
    printf("%d人目の年齢を入力してください\n", i + 1);
    scanf("%d", &student[i].age);
    printf("%d人目の性別を入力してください(man または woman)\n", i + 1);
    scanf("%s", &student[i].gender);
  }
}
