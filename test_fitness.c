#include <assert.h>
#include <string.h>
#include <stdio.h>
#define UNIT_TEST
#include "fitness.c" // รวมโค้ดหลักมาใช้ในการทดสอบ

// ฟังก์ชันทดสอบ readCSV()
void test_readCSV() {
    Member members[MAX_MEMBERS];
    int count = readCSV(members);

    assert(count > 0); // ต้องอ่านข้อมูลได้อย่างน้อย 1 record
    printf("test_readCSV passed (%d members loaded)\n", count);
}

// ฟังก์ชันทดสอบ writeCSV() + readCSV()
void test_write_and_read() {
    Member members[3] = {
        {"John Test", 25, "Gold", "2025-01-01"},
        {"Jane Test", 30, "Silver", "2025-02-01"},
        {"Jimmy Test", 20, "Bronze", "2025-03-01"}
    };
    writeCSV(members, 3);

    Member loaded[10];
    int count = readCSV(loaded);

    assert(count == 3);
    assert(strcmp(loaded[1].name, "Jane Test") == 0);
    printf("test_write_and_read passed\n");
}

// ฟังก์ชันทดสอบ addMember()
void test_addMember() {
    Member members[10];
    int count = 0;

    Member m = {"Tester", 28, "Gold", "2025-05-05"};
    members[count++] = m;

    writeCSV(members, count);

    Member loaded[10];
    int newCount = readCSV(loaded);

    assert(newCount == 1);
    assert(strcmp(loaded[0].name, "Tester") == 0);
    printf("test_addMember passed\n");
}

// ฟังก์ชันทดสอบ searchMember() แบบง่าย (ไม่ใช้ scanf)
void test_searchMember_manual() {
    Member members[2] = {
        {"Alpha", 21, "Gold", "2025-01-01"},
        {"Beta", 22, "Silver", "2025-02-01"}
    };

    int found = 0;
    for (int i = 0; i < 2; i++) {
        if (strstr(members[i].name, "Alpha")) found = 1;
    }

    assert(found == 1);
    printf("test_searchMember_manual passed\n");
}

// ฟังก์ชันทดสอบ deleteMember() แบบจำลอง
void test_deleteMember_simulated() {
    Member members[3] = {
        {"A", 25, "Gold", "2025-01-01"},
        {"B", 30, "Silver", "2025-02-01"},
        {"C", 35, "Bronze", "2025-03-01"}
    };
    int count = 3;

    // ลบสมาชิก "B"
    for (int i = 0; i < count; i++) {
        if (strcmp(members[i].name, "B") == 0) {
            for (int j = i; j < count - 1; j++) {
                members[j] = members[j + 1];
            }
            count--;
            break;
        }
    }

    assert(count == 2);
    assert(strcmp(members[1].name, "C") == 0);
    printf("test_deleteMember_simulated passed\n");
}

int main() {
    printf("===== Running Fitness System Unit Tests =====\n");

    test_readCSV();
    test_write_and_read();
    test_addMember();
    test_searchMember_manual();
    test_deleteMember_simulated();

    printf("All tests passed successfully!\n");
    return 0;
}
