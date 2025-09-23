#define MAX_MEMBERS 100

typedef struct {
    char name[50];
    int age;
    char membershipType[20];
    char registrationDate[15];
} Member;

Member members[MAX_MEMBERS];
int memberCount = 0;
