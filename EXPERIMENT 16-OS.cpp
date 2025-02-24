#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employee.dat"

struct Employee {
    int id;
    char name[50];
    float salary;
};

void addEmployee(FILE *file, int position) {
    struct Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    getchar();
    printf("Enter name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0';
    printf("Enter salary: ");
    scanf("%f", &emp.salary);
    
    fseek(file, position * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
}

void readEmployee(FILE *file, int position) {
    struct Employee emp;
    fseek(file, position * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);
    
    if (feof(file)) {
        printf("No employee at position %d.\n", position);
    } else {
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
}

void updateEmployee(FILE *file, int position) {
    struct Employee emp;
    printf("Enter new ID: ");
    scanf("%d", &emp.id);
    getchar();
    printf("Enter new name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0';
    printf("Enter new salary: ");
    scanf("%f", &emp.salary);
    
    fseek(file, position * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
}

int main() {
    FILE *file = fopen(FILE_NAME, "r+b");
    if (!file) {
        file = fopen(FILE_NAME, "w+b");
        if (!file) { printf("Error opening file.\n"); return 1; }
    }
    
    int choice, position;
    while (1) {
        printf("\n1. Add Employee\n2. Read Employee\n3. Update Employee\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter position: ");
                scanf("%d", &position);
                addEmployee(file, position);
                break;
            case 2:
                printf("Enter position: ");
                scanf("%d", &position);
                readEmployee(file, position);
                break;
            case 3:
                printf("Enter position: ");
                scanf("%d", &position);
                updateEmployee(file, position);
                break;
            case 4:
                fclose(file);
                return 0;
        }
    }

    return 0;
}
