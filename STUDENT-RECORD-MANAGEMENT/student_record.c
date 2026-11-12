#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float grade;
};

void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");
    printf("Enter ID: "); scanf("%d", &s.id);
    printf("Enter Name: "); scanf(" %[^\n]", s.name);
    printf("Enter Age: "); scanf("%d", &s.age);
    printf("Enter Grade: "); scanf("%f", &s.grade);
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("✅ Student added successfully!\n\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    printf("\n📋 Student Records:\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("ID: %d, Name: %s, Age: %d, Grade: %.2f\n", s.id, s.name, s.age, s.grade);
    }
    fclose(fp);
    printf("\n");
}

void searchStudent() {
 int id;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    printf("Enter ID to search: "); scanf("%d", &id);
    int found = 0;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("🔍 Found: Name: %s, Age: %d, Grade: %.2f\n\n", s.name, s.age, s.grade);
            found = 1;
            break;
        }
    }
    if (!found) printf("❌ Student not found.\n\n");
    fclose(fp);
}

void updateStudent() {
    int id;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb+");
    printf("Enter ID to update: "); scanf("%d", &id);
    int found = 0;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Enter new Name: "); scanf(" %[^\n]", s.name);
            printf("Enter new Age: "); scanf("%d", &s.age);
            printf("Enter new Grade: "); scanf("%f", &s.grade);
            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            printf("✅ Record updated!\n\n");
            found = 1;
            break;
  }
    }
    if (!found) printf("❌ Student not found.\n\n");
    fclose(fp);
}

void deleteStudent() {
    int id;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    printf("Enter ID to delete: "); scanf("%d", &id);
    int found = 0;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");
    if (found) printf("🗑 Record deleted.\n\n");
    else printf("❌ Student not found.\n\n");
}

int main() {
    int choice;
    while (1) {
        printf("📚 Student Record Management\n");
        printf("1. Add Student\n2. Display All\n3. Search\n4. Update\n5. Delete\n6. Exit\n");
        printf("Choose an option: "); scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("⚠ Invalid choice.\n\n");
        }
    }
    return 0;
}
