#include <stdio.h>

struct dob {
    int day;
    int month;
    int year;
};

struct studentInfo {
    int rollNo;
    char name[50];
    float CGPA;
    struct dob age;
};

void studentByValue(struct studentInfo student) {
  printf("Call by Value:\n");
  printf("Roll No: %d , Name: %s ,CGPA: %.2f ,Date of Birth: %02d/%02d/%04d\n", student.rollNo, student.name,
         student.CGPA, student.age.day,
         student.age.month, student.age.year
  );
  printf("\n");
}


void studentByAddress(struct studentInfo *student) {
  printf("Call by Address:\n");
  printf("Roll No: %d , Name: %s ,CGPA: %.2f ,Date of Birth: %02d/%02d/%04d\n", student->rollNo, student->name,
         student->CGPA, student->age.day,
         student->age.month, student->age.year
  );
}

int main() {

  struct studentInfo student = {2939, "Souradip Saha", 8.5, {18, 01, 2004}};

  studentByValue(student);

  studentByAddress(&student);

  return 0;
}
