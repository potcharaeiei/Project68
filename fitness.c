#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 100

// โครงสร้างข้อมูลสมาชิก
typedef struct {
    char name[50];
    int age;
    char membershipType[20];
    char registrationDate[15];
} Member;

Member members[MAX_MEMBERS];
int memberCount = 0;

// โหลดข้อมูลจากไฟล์ CSV
void load_from_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("ไม่พบไฟล์ %s เริ่มต้นด้วยข้อมูลว่าง\n", filename);
        return;
    }
    char line[200];
    fgets(line, sizeof(line), file); // ข้าม header
    while (fgets(line, sizeof(line), file)) {
        Member m;
        char ageStr[10];
        sscanf(line, "%49[^,],%9[^,],%19[^,],%14[^\n]",
               m.name, ageStr, m.membershipType, m.registrationDate);
        m.age = atoi(ageStr);
        members[memberCount++] = m;
    }
    fclose(file);
}

// บันทึกข้อมูลลงไฟล์ CSV
void save_to_csv(const char *filename) {
    FILE *file = fopen(filename, "w");
    fprintf(file, "MemberName,Age,MembershipType,RegistrationDate\n");
    for (int i = 0; i < memberCount; i++) {
        fprintf(file, "%s,%d,%s,%s\n",
                members[i].name, members[i].age,
                members[i].membershipType, members[i].registrationDate);
    }
    fclose(file);
}

int main() {
    const char *filename = "members.csv";
    load_from_csv(filename);   // โหลดข้อมูล
    save_to_csv(filename);     // บันทึกข้อมูลกลับ
    printf("โหลดและบันทึกข้อมูลเรียบร้อยแล้ว (ยังไม่มีเมนู)\n");
    return 0;
}
