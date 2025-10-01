#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_MEMBERS 1000
#define FILE_NAME "members.csv"

typedef struct {
    char name[50];
    int age;
    char membershipType[20];
    char registrationDate[20];
} Member;

// อ่านข้อมูลจาก CSV file
int readCSV(Member members[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("File %s not found\n", FILE_NAME);
        return 0;
    }

    char line[MAX_LINE];
    int count = 0;

    // ข้าม header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, " %49[^,],%d,%19[^,],%19[^\n]",
               members[count].name,
               &members[count].age,
               members[count].membershipType,
               members[count].registrationDate);
        count++;
    }

    fclose(file);
    return count;
}

// เขียนข้อมูลลง CSV file
void writeCSV(Member members[], int count) {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Cannot write file\n");
        return;
    }

    // เขียน header
    fprintf(file, "Name,Age,MembershipType,RegistrationDate\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%d,%s,%s\n",
                members[i].name,
                members[i].age,
                members[i].membershipType,
                members[i].registrationDate);
    }

    fclose(file);
}

// ฟังก์ชั่นที่ 2.เพิ่มสมาชิก
void addMember(Member members[], int *count) {
    Member newMem;

    printf("Enter name: ");
    scanf(" %[^\n]", newMem.name);
    printf("Enter age: ");
    scanf("%d", &newMem.age);
    printf("Enter membership type (Gold/Silver/Bronze): ");
    scanf(" %[^\n]", newMem.membershipType);
    printf("Enter registration date (YYYY-MM-DD): ");
    scanf(" %[^\n]", newMem.registrationDate);

    members[*count] = newMem;
    (*count)++;

    writeCSV(members, *count);
    printf("Member added successfully!\n");
}

// ฟังก์ชั่นที่ 3.ค้นหาสมาชิก
void searchMember(Member members[], int count) {
    char keyword[50];
    int found = 0;

    printf("Enter name or membership type to search: ");
    scanf(" %[^\n]", keyword);

    for (int i = 0; i < count; i++) {
        if (strstr(members[i].name, keyword) || strstr(members[i].membershipType, keyword)) {
            printf("Found: %s | Age %d | %s | %s\n",
                   members[i].name,
                   members[i].age,
                   members[i].membershipType,
                   members[i].registrationDate);
            found = 1;
        }
    }

    if (!found) {
        printf("No member found\n");
    }
}

// ฟังก์ชั่นที่ 4.อัปเดตสมาชิก
void updateMember(Member members[], int count) {
    char name[50];
    int found = 0;

    printf("Enter the name of the member to update: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(members[i].name, name) == 0) {
            printf("Current data: %s | Age %d | %s | %s\n",
                   members[i].name,
                   members[i].age,
                   members[i].membershipType,
                   members[i].registrationDate);

            printf("New age: ");
            scanf("%d", &members[i].age);
            printf("New membership type: ");
            scanf(" %[^\n]", members[i].membershipType);
            printf("New registration date (YYYY-MM-DD): ");
            scanf(" %[^\n]", members[i].registrationDate);

            writeCSV(members, count);
            printf("Update successful!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Member not found\n");
    }
}

// ฟังก์ชั่นที่ 5.ลบสมาชิก
void deleteMember(Member members[], int *count) {
    char name[50];
    int found = 0;

    printf("Enter the name of the member to delete: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < *count; i++) {
        if (strcmp(members[i].name, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                members[j] = members[j + 1];
            }
            (*count)--;

            writeCSV(members, *count);
            printf("Member deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Member not found\n");
    }
}

// แสดงเมนู
void displayMenu() {
    printf("\n===== Fitness Member Management System =====\n");
    printf("1. Show all members\n");
    printf("2. Add new member\n");
    printf("3. Search member\n");
    printf("4. Update member\n");
    printf("5. Delete member\n");
    printf("0. Exit program\n");
    printf("Enter your choice: ");
}

int main() {
    Member members[MAX_MEMBERS];
    int count = readCSV(members);
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- Member List ---\n");
                for (int i = 0; i < count; i++) {
                    printf("%s | Age %d | %s | %s\n",
                           members[i].name,
                           members[i].age,
                           members[i].membershipType,
                           members[i].registrationDate);
                }
                break;
            case 2:
                addMember(members, &count);
                break;
            case 3:
                searchMember(members, count);
                break;
            case 4:
                updateMember(members, count);
                break;
            case 5:
                deleteMember(members, &count);
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}