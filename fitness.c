#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "members.csv"

struct Member {
    char name[50];
    char membership[20];
};

// ฟังก์ชันเพิ่มสมาชิก
void addMember() {
    struct Member m;
    FILE *fp = fopen(FILENAME, "a");
    if (fp == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }
    printf("กรอกชื่อสมาชิก: ");
    scanf("%s", m.name);
    printf("เลือกประเภทสมาชิก (Gold/Silver/Bronze): ");
    scanf("%s", m.membership);

    fprintf(fp, "%s,%s\n", m.name, m.membership);
    fclose(fp);
    printf("เพิ่มสมาชิกเรียบร้อยแล้ว!\n");
}

// ฟังก์ชันแสดงสมาชิกทั้งหมด
void showMembers() {
    struct Member m;
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("ไม่พบไฟล์สมาชิก\n");
        return;
    }

    printf("\n--- รายชื่อสมาชิก ---\n");
    while (fscanf(fp, "%49[^,],%19[^\n]\n", m.name, m.membership) == 2) {
        printf("ชื่อ: %s | ประเภท: %s\n", m.name, m.membership);
    }
    fclose(fp);
}

// ฟังก์ชันแก้ไขประเภทสมาชิก
void editMember() {
    struct Member m;
    char name[50], newType[20];
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.csv", "w");
    int found = 0;

    if (fp == NULL || temp == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    printf("กรอกชื่อสมาชิกที่ต้องการแก้ไข: ");
    scanf("%s", name);

    while (fscanf(fp, "%49[^,],%19[^\n]\n", m.name, m.membership) == 2) {
        if (strcmp(m.name, name) == 0) {
            printf("พบสมาชิก %s (ประเภท: %s)\n", m.name, m.membership);
            printf("กรอกประเภทสมาชิกใหม่ (Gold/Silver/Bronze): ");
            scanf("%s", newType);
            fprintf(temp, "%s,%s\n", m.name, newType);
            found = 1;
        } else {
            fprintf(temp, "%s,%s\n", m.name, m.membership);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.csv", FILENAME);

    if (found)
        printf("แก้ไขเรียบร้อยแล้ว!\n");
    else
        printf("ไม่พบสมาชิกชื่อ %s\n", name);
}

// ฟังก์ชันลบสมาชิก
void removeMember() {
    struct Member m;
    char name[50];
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.csv", "w");
    int found = 0;

    if (fp == NULL || temp == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    printf("กรอกชื่อสมาชิกที่ต้องการลบ: ");
    scanf("%s", name);

    while (fscanf(fp, "%49[^,],%19[^\n]\n", m.name, m.membership) == 2) {
        if (strcmp(m.name, name) == 0) {
            found = 1;
            continue; // ข้ามไม่เขียนลงไฟล์ใหม่
        }
        fprintf(temp, "%s,%s\n", m.name, m.membership);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.csv", FILENAME);

    if (found)
        printf("ลบสมาชิกเรียบร้อยแล้ว!\n");
    else
        printf("ไม่พบสมาชิกชื่อ %s\n", name);
}

// เมนูหลัก
int main() {
    int choice;
    do {
        printf("\n===== ระบบจัดการสมาชิกฟิตเนส =====\n");
        printf("1. เพิ่มสมาชิก\n");
        printf("2. แสดงสมาชิกทั้งหมด\n");
        printf("3. แก้ไขประเภทสมาชิก\n");
        printf("4. ลบสมาชิก\n");
        printf("5. ออกจากโปรแกรม\n");
        printf("เลือกเมนู: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMember(); break;
            case 2: showMembers(); break;
            case 3: editMember(); break;
            case 4: removeMember(); break;
            case 5: printf("ออกจากโปรแกรม...\n"); break;
            default: printf("เลือกเมนูไม่ถูกต้อง!\n");
        }
    } while (choice != 5);

    return 0;
}
// คอมไพล์ด้วยคำสั่ง: gcc fitness.c -o fitness -lm