#define NUM 20
struct source{
    int id;
    char title[NUM];
    struct source *next;
};

struct date{
    int year;
    int month;
    int day;
};
struct cost{
    int price;
    char description[NUM];
    struct source sources;
    struct date dates;
    struct cost *next;
};

struct income{
    int price;
    char description[NUM];
    struct source sources;
    struct date dates;
    struct income *next;
};


struct user{
    char firstName[NUM];
    char lastName[NUM];
    char nCode[NUM];
    char phone[NUM];
    char email[NUM];
    char userName[NUM];
    char password[NUM];
    char passwordVerification[NUM];
    struct income incomes;
    struct cost costs;
    struct User *next;
}users;

