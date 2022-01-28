#define NUM 100

struct date
{
    int year;
    int month;
    int day;
    struct date *next;
};
struct cost
{
    int price;
    char source[NUM];
    char description[NUM];
    struct date dates;
    struct cost *next;
};

struct income
{
    int price;
    char source[NUM];
    char description[NUM];
    struct date dates;
    struct income *next;
};

struct user
{
    char firstName[NUM];
    char lastName[NUM];
    char nCode[10];
    char phone[11];
    char email[NUM];
    char userName[NUM];
    char password[NUM];
    struct income *userIncomes;
    struct cost *userCosts;
    struct user *next;
} users;

struct ratio
{
    int source;
    int ratio;
    struct Ratio *next;
};

struct banUser
{
    char userName[NUM];
    int time;
    struct banUser *next;
};

typedef enum
{
    false = 0,
    true = 1
} bool;

char INCOME_SOURCE[4][50] = {"Programming rights !!!", "Subsidy.", "Family allowance money.", "University!"};
char COST_SOURCE[7][50] = {"Clothing.", "Travel.", "Tuition fees.", "Entertainment.", "Pay bills.", "Medical expenses.", "Charity help."};
char LOGIN_MENU[3][10] = {"Sign Up", "Login", "Exit"};
char MAIN_MENU[6][10] = {"Income", "Expenses", "Statistics", "Setting", "Sign Out", "Exit"};
char SETTING[3][15] = {"change phone", "change email","change password"};
char STATISTICS[3][20] = {"Incomes statistics", "Costs statistics", "Balance"};
char COST_MENU[9][50] = {"Total cost", "Total cost in a certain range", "Most cost", "Most cost in a certain range", "costs ratio", "Display one-period costs", "The amount of a certain cost", "Cost search", "Main menu"};
char INCOME_MENU[9][50] = {"Total income", "Total income in a certain range", "Most income", "Most income in a certain range", "Incomes ratio", "Display one-period incomes", "The amount of a certain income", "Income search", "Main menu"};
