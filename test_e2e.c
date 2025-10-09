#define UNIT_TEST  // ปิด main() ใน fitness.c
#include "fitness.c"
#include <assert.h>

// สร้างไฟล์ CSV ใหม่ก่อนเริ่มทดสอบ
void resetCSV() {
    FILE *f = fopen(FILE_NAME, "w");
    assert(f && "Cannot create test CSV");
    fprintf(f, "Name,Age,MembershipType,RegistrationDate\n");
    fclose(f);
}

// นับจำนวนบรรทัดในไฟล์ (ใช้ตรวจหลังเขียน)
int countLines(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    int ch, lines = 0;
    while ((ch = fgetc(f)) != EOF)
        if (ch == '\n') lines++;
    fclose(f);
    return lines;
}

// แสดงข้อมูลสมาชิก (debug)
void printMembers(Member *members, int count) {
    printf("--- Current Members (%d) ---\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%s | %d | %s | %s\n",
               members[i].name,
               members[i].age,
               members[i].membershipType,
               members[i].registrationDate);
    }
}

// ทดสอบเพิ่มและอ่านข้อมูล
void testAddAndRead() {
    printf("[E2E] testAddAndRead\n");
    resetCSV();
    Member members[MAX_MEMBERS];
    int count = readCSV(members);
    assert(count == 0);

    Member m = {"John Doe", 25, "Gold", "2024-01-01"};
    members[count++] = m;
    writeCSV(members, count);

    Member reloaded[MAX_MEMBERS];
    int readCount = readCSV(reloaded);
    assert(readCount == 1);
    assert(strcmp(reloaded[0].name, "John Doe") == 0);
    assert(strcmp(reloaded[0].membershipType, "Gold") == 0);
    assert(strcmp(reloaded[0].registrationDate, "2024-01-01") == 0);
    printf("Passed: Add + Read CSV\n");
}

// ทดสอบอัปเดตข้อมูล
void testUpdate() {
    printf("[E2E] testUpdate\n");
    Member members[MAX_MEMBERS];
    int count = readCSV(members);
    assert(count == 1);

    strcpy(members[0].membershipType, "Silver");
    members[0].age = 30;
    strcpy(members[0].registrationDate, "2025-03-15");
    writeCSV(members, count);

    Member verify[MAX_MEMBERS];
    int n = readCSV(verify);
    assert(n == 1);
    assert(strcmp(verify[0].membershipType, "Silver") == 0);
    assert(verify[0].age == 30);
    assert(strcmp(verify[0].registrationDate, "2025-03-15") == 0);
    printf("Passed: Update Member\n");
}

// ทดสอบค้นหาสมาชิก
void testSearch() {
    printf("[E2E] testSearch\n");
    resetCSV();
    Member members[MAX_MEMBERS];
    int count = 0;

    Member a = {"Alice", 21, "Gold", "2024-07-07"};
    Member b = {"Bob", 30, "Bronze", "2023-02-10"};
    members[count++] = a;
    members[count++] = b;
    writeCSV(members, count);

    Member loaded[MAX_MEMBERS];
    int n = readCSV(loaded);
    assert(n == 2);

    int found = 0;
    for (int i = 0; i < n; ++i) {
        if (strstr(loaded[i].membershipType, "Gold"))
            found++;
    }
    assert(found == 1);
    printf("Passed: Search Member\n");
}

// ทดสอบลบสมาชิก
void testDelete() {
    printf("[E2E] testDelete\n");
    Member members[MAX_MEMBERS];
    int count = readCSV(members);
    assert(count == 2);

    count = 1; // ลบ 1 คน (ลบ Bob)
    writeCSV(members, count);

    int lines = countLines(FILE_NAME);
    assert(lines == 2); // header + 1 member
    printf("Passed: Delete Member\n");
}

// main test runner
int main(void) {
    printf("Running End-to-End Tests for fitness.c\n\n");

    testAddAndRead();
    testUpdate();
    testSearch();
    testDelete();

    printf("\nAll E2E tests passed successfully!\n");
    return 0;
}

/* gcc -std=c11 -Wall -Wextra test_e2e.c -o test_e2e
.\test_e2e */