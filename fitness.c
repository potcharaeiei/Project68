#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 100
#define FILE_NAME "members.csv"

typedef struct {
    char name[50];
    int age;
    char membershipType[20];  
    char registrationDate[20];
} Member;

Member members[MAX_MEMBERS];
int memberCount = 0;

// ฟังก์ชันประกาศ
void display_menu() {
    printf("\n===== ระบบจัดการสมาชิกฟิตเนส =====\n");
    printf("1. เพิ่มสมาชิกใหม่\n");
    printf("2. แสดงข้อมูลสมาชิกทั้งหมด\n");
    printf("3. ค้นหาสมาชิก\n");
    printf("4. แก้ไขข้อมูลสมาชิก\n");
    printf("5. ลบสมาชิก\n");
    printf("6. บันทึกลงไฟล์ CSV\n");
    printf("7. อ่านข้อมูลจากไฟล์ CSV\n");
    printf("8. ออกจากโปรแกรม\n");
    printf("เลือกเมนู: ");
}

// ฟังก์ชันเพิ่มสมาชิกใหม่
void add_member() {
    if (memberCount >= MAX_MEMBERS) {
        printf("ไม่สามารถเพิ่มสมาชิกได้ (เต็ม)\n");
        return;
    }
    Member m;
    printf("ป้อนชื่อสมาชิก: ");
    scanf(" %[^\n]", m.name);
    printf("ป้อนอายุ: ");
    scanf("%d", &m.age);
    printf("ป้อนประเภทสมาชิก (Gold/Silver/Bronze): ");
    scanf(" %[^\n]", m.membershipType);
    printf("ป้อนวันที่สมัคร (YYYY-MM-DD): ");
    scanf(" %[^\n]", m.registrationDate);


    members[memberCount++] = m;
    printf("เพิ่มข้อมูลสมาชิกเรียบร้อยแล้ว!\n");
}

void show_members() {
    if (memberCount == 0) {
        printf("ยังไม่มีข้อมูลสมาชิก\n");
        return;
    }
    printf("\n--- รายชื่อสมาชิกทั้งหมด ---\n");
    for (int i = 0; i < memberCount; i++) {
        printf("%d. %s | อายุ: %d | ประเภท: %s | วันที่สมัคร: %s\n", 
               i + 1, members[i].name, members[i].age, members[i].membershipType, members[i].registrationDate);
    }
}

void search_member() {
    char keyword[50];
    printf("ป้อนชื่อหรือประเภทสมาชิกที่ต้องการค้นหา: ");
    scanf(" %[^\n]", keyword);

    int found = 0;
    for (int i = 0; i < memberCount; i++) {
        if (strstr(members[i].name, keyword) || strstr(members[i].membershipType, keyword)) {
            printf("พบ: %s | อายุ: %d | ประเภท: %s | วันที่สมัคร: %s\n", 
                   members[i].name, members[i].age, members[i].membershipType, members[i].registrationDate);
            found = 1;
        }
    }
    if (!found) {
        printf("ไม่พบข้อมูลสมาชิก\n");
    }
}

void update_member() {
    char name[50];
    printf("ป้อนชื่อสมาชิกที่ต้องการแก้ไข: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].name, name) == 0) {
            printf("ป้อนอายุใหม่: ");
            scanf("%d", &members[i].age);
            printf("ป้อนประเภทสมาชิกใหม่ (Gold/Silver/Bronze): ");
            scanf(" %[^\n]", members[i].membershipType);
            printf("ป้อนวันที่สมัครใหม่ (YYYY-MM-DD): ");
            scanf(" %[^\n]", members[i].registrationDate);
            printf("แก้ไขข้อมูลเรียบร้อย!\n");
            return;
        }
    }
    printf("ไม่พบชื่อสมาชิก\n");
}

void delete_member() {
    char name[50];
    printf("ป้อนชื่อสมาชิกที่ต้องการลบ: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].name, name) == 0) {
            for (int j = i; j < memberCount - 1; j++) {
                members[j] = members[j + 1];
            }
            memberCount--;
            printf("ลบข้อมูลสมาชิกเรียบร้อย!\n");
            return;
        }
    }
    printf("ไม่พบชื่อสมาชิก\n");
}

void save_to_csv() {
    FILE *fp = fopen("members.csv", "w");
    if (!fp) {
        printf("ไม่สามารถบันทึกไฟล์ได้\n");
        return;
    }
    fprintf(fp, "MemberName,Age,MembershipType,RegistrationDate\n");
    for (int i = 0; i < memberCount; i++) {
        fprintf(fp, "%s,%d,%s,%s\n", members[i].name, members[i].age, members[i].membershipType, members[i].registrationDate);
    }

    fclose(fp);
    printf("บันทึกข้อมูลลง members.csv เรียบร้อยแล้ว!\n");
}

void load_from_csv() {
    FILE *fp = fopen("members.csv", "r");
    if (!fp) {
        printf(" ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    char line[200];
    fgets(line, sizeof(line), fp); // ข้าม header

    memberCount = 0;
    while (fgets(line, sizeof(line), fp)) {
        Member m;
        sscanf(line, "%[^,],%d,%[^,],%s", m.name, &m.age, m.membershipType, m.registrationDate);
        members[memberCount++] = m;
    }
    fclose(fp);
    printf(" โหลดข้อมูลจาก members.csv เรียบร้อยแล้ว!\n");
}

int main() {
    int choice;
    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_member(); break;
            case 2: show_members(); break;
            case 3: search_member(); break;
            case 4: update_member(); break;
            case 5: delete_member(); break;
            case 6: save_to_csv(); break;
            case 7: load_from_csv(); break;
            case 8: printf("ออกจากโปรแกรม...\n"); break;
            default: printf(" เลือกเมนูไม่ถูกต้อง ลองใหม่อีกครั้ง\n");
        }
    } while (choice != 8);

    return 0;
}

//ถ้ารันแล้วเจอปัญหาเรื่องภาษาไทย ให้รันคำสั่งนี้ใน PowerShell ก่อน
//[Console]::OutputEncoding = [System.Text.Encoding]::UTF8 
//.\fitness.exe