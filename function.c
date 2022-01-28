#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM 50

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

typedef enum {false = 0,true = 1} bool;

char INCOME_SOURCE[4][50] = {"Programming rights !!!", "Subsidy.", "Family allowance money.", "University!"};
char COST_SOURCE[7][50] = {"Clothing.", "Travel.", "Tuition fees.", "Entertainment.", "Pay bills.", "Medical expenses.", "Charity help."};
char LOGIN_MENU[3][20] = {"Sign Up", "Login", "Exit"};
char MAIN_MENU[6][20] = {"Income", "Expenses", "Statistics", "Setting", "Sign Out", "Exit"};
char SETTING[3][20] = {"change phone", "change email", "change password"};
char STATISTICS[3][20] = {"Incomes statistics", "Costs statistics", "Balance"};
char COST_MENU[9][50] = {"Total cost", "Total cost in a certain range", "Most cost", "Most cost in a certain range", "costs ratio", "Display one-period costs", "The amount of a certain cost", "Cost search", "Main menu"};
char INCOME_MENU[9][50] = {"Total income", "Total income in a certain range", "Most income", "Most income in a certain range", "Incomes ratio", "Display one-period incomes", "The amount of a certain income", "Income search", "Main menu"};

void clear()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

bool VerifyNcode(char nCode[])
{
    int len = 10, i;
    bool result = true;
    if (strlen(nCode) == len)
    {
        for (i = 0; i < len; i++)
        {
            if (isdigit(nCode[i]) != 1)
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;

    return result;
}

bool VerifyPhone(char phone[])
{
    int len = 11, i;
    bool result = true;
    if (strlen(phone) == len)
    {
        if (phone[0] == '0' && phone[1] == '9')
        {
            for (i = 0; i < len; i++)
            {
                if (isdigit(phone[i]) != 1)
                {
                    result = false;
                    break;
                }
            }
        }
        else
            result = false;
    }
    else
        result = false;

    return result;
}

bool VerifyPassword(char pass[])
{
    int len = 10, i = 0, digit = 0, alpha = 0, character = 0;
    bool result = true;

    if (strlen(pass) >= len)
    {
        while (pass[i] != '\0')
        {
            if (pass[i] == '%' || pass[i] == '@' || pass[i] == '*')
                character++;
            else if (isdigit(pass[i]) == 1)
                digit++;
            else if (isalpha(pass[i]) == 2)
                alpha++;
            else
            {
                result = false;
                break;
            }
            i++;
        }
        if (character == 0 || alpha == 0 || digit == 0)
            result = false;
    }
    else
        result = false;

    return result;
}

bool VerifyEmail(char email[])
{
    int len = 15, i = 0;
    bool result = false;

    if (strlen(email) >= len)
    {
        while (email[i] != '\0')
        {
            if (email[i] == '@')
            {
                result = true;
                break;
            }
            i++;
        }
    }
    return result;
}

bool VerifyUserName(char userName[])
{
    int len = 8, i = 0;
    bool result = true;

    if (strlen(userName) >= len)
    {
        while (userName[i] != '\0')
        {
            if ((userName[i] >= 'a' && userName[i] <= 'z') || (userName[i] >= 'A' && userName[i] <= 'Z') ||
                (userName[i] >= '0' && userName[i] <= '9'))
                result = true;
            else
            {
                result = false;
                break;
            }
            i++;
        }
    }
    else
        result = false;

    return result;
}

bool Verify(struct user users)
{
    return ((VerifyNcode(users.nCode) == true) && (VerifyPhone(users.phone) == true) && (VerifyPassword(users.password) == true) && (VerifyEmail(users.email) == true) && (VerifyUserName(users.userName) == true));
}

struct user GetSignUpData()
{
    struct user users;
    char passVr[NUM], pass[NUM];
    int i = 0;
    printf("first name: ");
    gets(users.firstName);
    printf("\nlast name: ");
    gets(users.lastName);
    printf("\nuser name: ");
    scanf("%s", users.userName);
    clear();
    printf("\nnational code: ");
    scanf("%s", users.nCode);
    clear();
    printf("\nphone number: ");
    scanf("%s", users.phone);
    clear();
    printf("\nemail address: ");
    scanf("%s", users.email);
    clear();
    do
    {
        printf("\npassword: ");
        while ((pass[i] = getch()) != '\n' && pass[i] != '\r')
        {
            printf("*");
            i++;
        }
        pass[i] = '\0';
        strcpy(users.password, pass);
        i = 0;
        printf("\nPassword verification: ");
        while ((passVr[i] = getch()) != '\n' && passVr[i] != '\r')
        {
            printf("*");
            i++;
        }
        passVr[i] = '\0';
    } while (strcmp(users.password, passVr) != 0);
    users.userIncomes = NULL;
    users.userCosts = NULL;
    return users;
}

bool AddNewUser(struct user users)
{
    char name[50], address[100] = "./users/";
    strcpy(name, users.userName);
    strcat(name, ".txt");
    strcat(address, name);

    int test;
    FILE *fp;
    fp = fopen(address, "w+");
    if (fp == NULL)
        return false;

    else
    {
        test = fwrite(&users, sizeof(struct user), 1, fp);
        if (test != 1)
            return false;
    }
    fclose(fp);
    return true;
}

void GetUserName(char *userName)
{
    printf("please enter your user name: ");
    scanf("%s", userName);
    clear();
}

bool CheckUserNameExist(char userNames[])
{
    char name[50], address[100] = "./users/";
    strcpy(name, userNames);
    strcat(name, ".txt");
    strcat(address, name);
    FILE *fp;
    fp = fopen(address, "r");
    if (fp == NULL)
        return false;
    fclose(fp);
    return true;
}

bool BanUserName(char userName[])
{

    bool result = true;
    int test;
    struct banUser newBanUser;
    strcpy(newBanUser.userName, userName);
    newBanUser.time = time(NULL);
    FILE *fp;
    fp = fopen("banUser.txt", "a+");
    if (fp == NULL)
        result = false;
    else
    {
        test = fwrite(&newBanUser, sizeof(struct banUser), 1, fp);
        if (test != 1)
            result = false;
    }
    fclose(fp);
    return result;
}

bool CheckUserNameNotBan(char userName[])
{

    int timer = time(NULL);
    FILE *fp;
    fp = fopen("banUser.txt", "r+");
    if (fp == NULL)
        printf("file could not be opened!!");
    else
    {
        while (1 == 1)
        {
            struct banUser *temp;
            temp = (struct banUser *)malloc(sizeof(struct banUser));

            if (fread(temp, sizeof(struct banUser), 1, fp) == 0)
                break;
            if (strcmp(temp->userName, userName) == 0 && temp->time - timer > 15 * 60)
            {
                fclose(fp);
                return true;
            }
        }
    }
    fclose(fp);
    return false;
}

void GetPassword(char *pass)
{
    int i = 0;
    printf("Please Enter Password: ");
    while ((pass[i] = getch()) != '\n' && pass[i] != '\r')
    {
        printf("*");
        i++;
    }
    pass[i] = '\0';
}

bool CheckPasswordRight(char userName[], char password[])
{
    bool result = true;
    struct user users;
    char name[50], address[100] = "./users/";
    strcpy(name, userName);
    strcat(name, ".txt");
    strcat(address, name);
    FILE *fp;
    fp = fopen(address, "r");
    if (fp == NULL)
        result = false;
    else
    {
        fread(&users, sizeof(struct user), 1, fp);
        if (strcmp(users.userName, userName) == 0)
        {
            if (strcmp(users.password, password) != 0)
                result = false;
        }
        else
            result = false;
    }
    fclose(fp);
    return result;
}

struct income *ReadInCome(char username[])
{
    char name[50], address[100] = "./income/";
    strcpy(name, username);
    strcat(name, ".txt");
    strcat(address, name);

    struct income *head;
    FILE *fp;
    fp = fopen(name, "r");
    if (fp == NULL)
        printf("file could not be opened!!");
    else
    {
        struct income *temp;
        temp = (struct income *)malloc(sizeof(struct income));
        fread(temp, sizeof(struct income), 1, fp);
        temp->next = NULL;
        head = temp;
    }
    fclose(fp);

    return head;
}

struct cost *ReadCost(char username[])
{
    char name[50], address[100] = "./cost/";
    strcpy(name, username);
    strcat(name, ".txt");
    strcat(address, name);

    struct cost *head;
    FILE *fp;
    fp = fopen(name, "r");
    if (fp == NULL)
        printf("file could not be opened!!");
    else
    {
        struct cost *temp;
        temp = (struct cost *)malloc(sizeof(struct cost));
        fread(temp, sizeof(struct cost), 1, fp);
        temp->next = NULL;
        head = temp;
    }
    fclose(fp);
    return head;
}

struct user ReadData(struct user userData)
{
    userData.userIncomes = ReadInCome(userData.userName);
    userData.userCosts = ReadCost(userData.userName);

    return userData;
}

struct income ReadNewInComeData()
{
    struct income newIncome;
    int IDInComeSource;
    printf("Income amount: ");
    scanf("%d", &newIncome.price);
    printf("\nIncome source number: \n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s \n", i + 1, INCOME_SOURCE[i]);
    }
    printf("please enter your choice: ");
    scanf("%d", &IDInComeSource);
    strcpy(newIncome.source, INCOME_SOURCE[IDInComeSource - 1]);

    printf("\nIncome Date (yyyy/mm/dd): ");
    scanf("%d%*c%d%*c%d", &newIncome.dates.year, &newIncome.dates.month, &newIncome.dates.day);
    printf("Description (within one line): ");
    gets(newIncome.description);
    clear();

    return newIncome;
}

bool AddInComeToFile(struct income incomes, struct user users)
{
    bool result = true;
    int test;
    char name[50], address[100] = "./income/";
    strcpy(name, users.userName);
    strcat(name, ".txt");
    strcat(address, name);

    FILE *fp;
    fp = fopen(address, "a+");
    if (fp == NULL)
        result = false;

    else
    {
        test = fwrite(&incomes, sizeof(struct income), 1, fp);
        if (test != 1)
            result = false;
    }
    fclose(fp);

    return result;
}

bool AddInComeToLinkedList(struct income newIncome, struct user users)
{
    struct income *tempIncome;
    tempIncome = users.userIncomes;
    if (tempIncome == NULL)
    {
        tempIncome = (struct income *)malloc(sizeof(struct income));
        tempIncome->price = newIncome.price;
        strcpy(tempIncome->source, newIncome.source);
        tempIncome->dates.year = newIncome.dates.year;
        tempIncome->dates.month = newIncome.dates.month;
        tempIncome->dates.day = newIncome.dates.day;
        strcpy(tempIncome->description, newIncome.description);
        tempIncome->next = NULL;
        users.userIncomes = tempIncome;
    }
    else
    {
        while (tempIncome->next != NULL)
        {
            tempIncome = tempIncome->next;
        }
        tempIncome->next = (struct income *)malloc(sizeof(struct income));
        tempIncome = tempIncome->next;
        tempIncome->price = newIncome.price;
        strcpy(tempIncome->source, newIncome.source);
        tempIncome->dates.year = newIncome.dates.year;
        tempIncome->dates.month = newIncome.dates.month;
        tempIncome->dates.day = newIncome.dates.day;
        strcpy(tempIncome->description, newIncome.description);
        tempIncome->next = NULL;
    }
    return true;
}

bool AddInCome(struct income incomes, struct user uses)
{
    if (AddInComeToLinkedList(incomes, uses) == 1 &&
        AddInComeToFile(incomes, uses) == 1)
        return true;
    return false;
}

struct cost ReadNewCostData()
{
    struct cost newCost;
    int IDCostSource;
    printf("Amount of expenses: ");
    scanf("%d", &newCost.price);
    printf("\nCost item: \n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d. %s \n", i + 1, COST_SOURCE[i]);
    }
    printf("please enter your choice: ");
    scanf("%d", &IDCostSource);
    strcpy(newCost.source, COST_SOURCE[IDCostSource - 1]);
    printf("\nCost Date (yyyy/mm/dd): ");
    scanf("%d%*c%d%*c%d", &newCost.dates.year, &newCost.dates.month, &newCost.dates.day);
    printf("Description (within one line): ");
    gets(newCost.description);
    clear();

    return newCost;
}

bool AddCostToFile(struct cost costs, struct user users)
{
    bool result = true;
    int test;
    char name[50], address[100] = "./cost/";
    strcpy(name, users.userName);
    strcat(name, ".txt");
    strcat(address, name);

    FILE *fp;
    fp = fopen(address, "a+");
    if (fp == NULL)
        result = false;
    else
    {
        test = fwrite(&costs, sizeof(struct cost), 1, fp);
        if (test != 1)
            result = false;
    }
    return result;
}

bool AddCostToLinkedList(struct cost newCost, struct user uses)
{
    struct cost *tempCost;
    tempCost = users.userCosts;
    if (tempCost == NULL)
    {
        tempCost = (struct cost *)malloc(sizeof(struct cost));
        tempCost->price = newCost.price;
        strcpy(tempCost->source, newCost.source);
        tempCost->dates.year = newCost.dates.year;
        tempCost->dates.month = newCost.dates.month;
        tempCost->dates.day = newCost.dates.day;
        strcpy(tempCost->description, newCost.description);
        tempCost->next = NULL;
        users.userCosts = tempCost;
    }
    else
    {
        while (tempCost->next != NULL)
        {
            tempCost = tempCost->next;
        }
        tempCost->next = (struct cost *)malloc(sizeof(struct cost));
        tempCost = tempCost->next;
        tempCost->price = newCost.price;
        strcpy(tempCost->source, newCost.source);
        tempCost->dates.year = newCost.dates.year;
        tempCost->dates.month = newCost.dates.month;
        tempCost->dates.day = newCost.dates.day;
        strcpy(tempCost->description, newCost.description);
        tempCost->next = NULL;
    }
    return true;
}

bool AddCost(struct cost costs, struct user uses)
{
    bool result = false;
    if (AddCostToLinkedList(costs, uses) &&
        AddCostToFile(costs, uses))
    {
        result = true;
    }
    return result;
}

int CompareDate(struct date startDate, struct date endDate)
{
    int output;

    if (startDate.year == endDate.year)
    {
        if (startDate.month < endDate.month)
            output = 1;
        else if (startDate.month > endDate.month)
            output = -1;
        else if (startDate.day == endDate.day)
            output = 0;
        else if (startDate.day > endDate.day)
            output = -1;
        else
            output = 1;
    }
    else if (startDate.year < endDate.year)
        output = 1;
    else
        output = -1;

    return output;
}

struct income *FilterIncome(struct date startDate, struct date endDate, char source[], struct income *head)
{
    struct income *curr = head;
    struct income *headFilter = (struct income *)malloc(sizeof(struct income));
    struct income *currFilter = NULL;
    currFilter = headFilter;

    while (curr != NULL)
    {
        if (strcmp(curr->source, source) == 0 && CompareDate(curr->dates, startDate) == 0)
        {
            while (CompareDate(curr->dates, startDate) == 1)
            {
                currFilter = curr;
                currFilter->next = (struct income *)malloc(sizeof(struct income));
                currFilter = currFilter->next;
            }
            currFilter->next = NULL;
            break;
        }
        curr = curr->next;
    }
    return headFilter;
}

struct income MaxIncome(struct income *headFilter)
{
    struct income maxI;
    maxI.price = 0;
    struct income *currFilter = headFilter;
    while (currFilter != NULL)
    {
        if (currFilter->price > maxI.price)
            maxI.price = currFilter->price;
        maxI.dates = currFilter->dates;
        strcmp(maxI.description, currFilter->description);
        strcmp(maxI.source, currFilter->source);

        currFilter = currFilter->next;
    }
    return maxI;
}

void RatioIncome(struct income *headFilter)
{
    int sum = 0, arrayCount[4] = {0, 0, 0, 0};
    struct income *currFilter = headFilter;
    while (currFilter != NULL)
    {
        sum += currFilter->price;
        arrayCount[atoi(currFilter->source)] += currFilter->price;
        currFilter = currFilter->next;
    }

    int i = 0;
    arrayCount[i] = (arrayCount[i] / sum) * 100;
    struct ratio *head, *last, *temp;
    temp = (struct ratio *)malloc(sizeof(struct ratio));
    temp->ratio = arrayCount[i];
    temp->source = i;
    temp->next = NULL;
    head = last = temp;
    for (i = 1; i < 4; i++)
    {
        arrayCount[i] = (arrayCount[i] / sum) * 100;
        temp = (struct ratio *)malloc(sizeof(struct ratio));
        temp->ratio = arrayCount[i];
        temp->source = i;
        temp->next = NULL;
        last->next = temp;
        last = temp;
    }
    temp = head;
    while (temp != NULL)
    {
        printf("%s = %d \t", INCOME_SOURCE[temp->source], temp->ratio);
        temp = temp->next;
    }
}

int SumIncome(struct income *headFilter)
{
    int sumI = 0;
    struct income *currFilter = headFilter;
    while (currFilter != NULL)
    {
        sumI += currFilter->price;
        currFilter = currFilter->next;
    }
    return sumI;
}

struct income *SearchIncome(char searchWord[], struct income *head)
{
    struct income *curr = head;
    struct income *headSearch = (struct income *)malloc(sizeof(struct income));
    struct income *currSearch = NULL;
    currSearch = headSearch;

    while (curr != NULL)
    {
        for (int i = 0; i < NUM; i++)
        {
            int result;
            if (strcmp(searchWord[0], INCOME_SOURCE[curr->source[i]]) == 0)
            {
                int k = i + 1;
                result = 1;
                for (int j = 1; j < strlen(searchWord); j++)
                {
                    if (strcmp(searchWord[j], INCOME_SOURCE[curr->source[k]]) != 0)
                    {
                        result = 0;
                        break;
                    }
                    k++;
                }
            }
            if (result == 1)
            {
                currSearch = curr;
                currSearch->next = (struct income *)malloc(sizeof(struct income));
                currSearch = currSearch->next;
                break;
            }
        }
        curr = curr->next;
    }
    return currSearch;
}

struct cost *FilterCost(struct date startDate, struct date endDate, int source, struct Cost *head)
{
    struct cost *curr = head;
    struct cost *headFilter = (struct cost *)malloc(sizeof(struct cost));
    struct cost *currFilter = NULL;
    currFilter = headFilter;

    while (curr != NULL)
    {
        if (strcmp(curr->source, source) == 0 && CompareDate(curr->dates, startDate) == 0)
        {
            while (CompareDate(curr->dates, startDate) == 1)
            {
                currFilter = curr;
                currFilter->next = (struct cost *)malloc(sizeof(struct cost));
                currFilter = currFilter->next;
            }
            currFilter->next = NULL;
            break;
        }
        curr = curr->next;
    }
    return headFilter;
}



struct cost MaxCost(struct cost *headFilter)
{
    struct cost maxC;
    maxC.price = 0;
    struct cost *currFilter = headFilter;
    while (currFilter != NULL)
    {
        if (currFilter->price > maxC.price)
            maxC.dates = currFilter->dates;
        strcmp(maxC.description, currFilter->description);
        maxC.price = currFilter->price;
        strcmp(maxC.source, currFilter->source);

        currFilter = currFilter->next;
    }
    return maxC;
}

void RatioCost(struct cost *headFilter)
{
    int sum = 0, arrayCount[7] = {0, 0, 0, 0, 0, 0, 0};
    struct cost *currFilter = headFilter;
    while (currFilter != NULL)
    {
        sum += currFilter->price;
        arrayCount[atoi(currFilter->source)] += currFilter->price;

        currFilter = currFilter->next;
    }

    int i = 0;
    arrayCount[i] = (arrayCount[i] / sum) * 100;
    struct ratio *head, *last, *temp;
    temp = (struct ratio *)malloc(sizeof(struct ratio));
    temp->ratio = arrayCount[i];
    temp->source = i;
    temp->next = NULL;
    head = last = temp;
    for (i = 1; i < 7; i++)
    {
        arrayCount[i] = (arrayCount[i] / sum) * 100;
        temp = (struct ratio *)malloc(sizeof(struct ratio));
        temp->ratio = arrayCount[i];
        temp->source = i;
        temp->next = NULL;
        last->next = temp;
        last = temp;
    }
    temp = head;
    while (temp != NULL)
    {
        printf("%s = %d \t", COST_SOURCE[temp->source], temp->ratio);
        temp = temp->next;
    }
}

int SumCost(struct cost *headFilter)
{
    int sumC = 0;
    struct cost *currFilter = headFilter;
    while (currFilter != NULL)
    {
        sumC += currFilter->price;
        currFilter = currFilter->next;
    }
    return sumC;
}

struct cost *SearchCost(char searchWord[], struct cost *head)
{
    struct cost *curr = head;
    struct cost *headSearch = (struct cost *)malloc(sizeof(struct cost));
    struct cost *currSearch = NULL;
    currSearch = headSearch;

    while (curr != NULL)
    {
        for (int i = 0; i < NUM; i++)
        {
            int result;
            if (strcmp(searchWord[0], COST_SOURCE[curr->source[i]]) == 0)
            {
                int k = i + 1;
                result = 1;
                for (int j = 1; j < strlen(searchWord); j++)
                {
                    if (strcmp(searchWord[j], INCOME_SOURCE[curr->source[k]]) != 0)
                    {
                        result = 0;
                        break;
                    }
                    k++;
                }
            }
            if (result == 1)
            {
                currSearch = curr;
                currSearch->next = (struct cost *)malloc(sizeof(struct cost));
                currSearch = currSearch->next;
                break;
            }
        }
        curr = curr->next;
    }
    return currSearch;
}

int Balance(struct user users)
{
    int totalIncome = 0, totalCost = 0;
    struct income *head, *last, *temp;

    FILE *fp1, *fp2;
    char name[50], addressC[100] = "./cost/", addressI[100] = "./income/";
    strcpy(name, users.userName);
    strcat(name, ".txt");
    strcat(addressC, name);

    fp1 = fopen(addressC, "r");
    if (fp1 == NULL)
        printf("file could not be opened!!");
    else
    {
        struct cost *headC, *lastC, *tempC;
        tempC = (struct cost *)malloc(sizeof(struct cost));
        fread(tempC, sizeof(struct cost), 1, fp1);
        tempC->next = NULL;
        headC = lastC = tempC;

        while (feof(fp1) == 0)
        {
            tempC = (struct cost *)malloc(sizeof(struct cost));
            fread(tempC, sizeof(struct cost), 1, fp1);
            tempC->next = NULL;
            lastC->next = tempC;
            lastC = tempC;
        }
        tempC = headC;
        while (tempC != NULL)
        {
            totalCost += tempC->price;
            tempC = tempC->next;
        }
    }
    fclose(fp1);

    strcat(addressI, name);

    fp2 = fopen(addressI, "r");
    if (fp2 == NULL)
        printf("file could not be opened!!");
    else
    {
        struct income *headI, *lastI, *tempI;
        tempI = (struct income *)malloc(sizeof(struct income));
        fread(tempI, sizeof(struct income), 1, fp2);
        tempI->next = NULL;
        headI = lastI = tempI;

        while (feof(fp2) == 0)
        {
            tempI = (struct income *)malloc(sizeof(struct income));
            fread(tempI, sizeof(struct income), 1, fp2);
            tempI->next = NULL;
            lastI->next = tempI;
            lastI = tempI;
        }
        tempI = headI;
        while (tempI != NULL)
        {
            totalIncome += tempI->price;
            tempI = tempI->next;
        }
    }
    fclose(fp2);

    int computing = totalIncome - totalCost;

    return computing;
}

struct user GetUserData(char username[])
{
    struct user userData;
    char address[100] = "./users/";
    strcat(username, ".txt");
    strcat(address, username);

    FILE *fp;
    fp = fopen(address, "r+");
    if (fp == NULL)
        printf("file could not be opened!!");
    else
    {
        fread(&userData, sizeof(struct user), 1, fp);
    }
    fclose(fp);
    return userData;
}

void ChangePassword(struct user users)
{
    char password[NUM], newPass[NUM], newPassVr[NUM];
    printf("Current password: ");
    scanf("%s", password);

    if (CheckPasswordRight(users.userName, password) == 1)
    {
        do
        {
            printf("\nnew password: ");
            scanf("%s", newPass);

            printf("\nnew Password verification: ");
            scanf("%s", newPassVr);

        } while (strcmp(newPass, newPassVr) != 0 && VerifyPassword(newPass) == 0 && VerifyPassword(newPassVr) == 0);
        strcpy(users.password, newPass);

        AddNewUser(users);
        printf("Changes were successfully recorded.");
    }
}

void ChangeEmail(struct user users)
{

    char pass[NUM], newEmail[NUM];
    printf("please enter password: ");
    scanf("%s", pass);

    if (strcmp(users.password, pass) == 0)
    {
        printf("\nnew email: ");
        scanf("%s", newEmail);
        if (VerifyEmail(newEmail) == 1)
            strcpy(users.email, newEmail);

        AddNewUser(users);
        printf("Changes were successfully recorded.");
    }
}

void ChangePhone(struct user users)
{
    char pass[NUM], newPhone[NUM];
    printf("please enter password: ");
    scanf("%s", pass);

    if (strcmp(users.password, pass) == 0)
    {
        printf("\nnew phone number: ");
        scanf("%s", newPhone);
        if (VerifyPhone(newPhone) == 1)
            strcpy(users.phone, newPhone);

        AddNewUser(users);
        printf("Changes were successfully recorded.");
    }
}

void LoginMenu()
{
    for (int i = 0; i < 3; i++)
    {
        printf("%d. %s \n", i + 1, LOGIN_MENU[i]);
    }
    int choice;
    do
    {
        printf(">>>please enter your choice: ");
        scanf("%d", &choice);
    } while (choice >= 1 && choice <= 3);

    if (choice == 1)
    {
        struct user newUser;
        bool success;
        do
        {
            newUser = GetSignUpData();
             success = Verify(newUser);
        } while (success == false);
        bool test = AddNewUser(newUser);
        if (test == true)
        {
            printf("\nSign Up completed successfully!!\n");
            MainMenu(newUser);
        }
        else
        {
            printf("\nSign Up failed!!\n");
            printf("Enter 1 to go to the previous menu: ");
            int menu;
            scanf("%d", &menu);
            if (menu == 1)
                LoginMenu();
        }
    }

    if (choice == 2)
    {
        char username[NUM];
        GetUserName(username);
        bool check = CheckUserNameExist(username);
        if (check == true)
        {
            char pass[NUM];
            do
            {
                int cou = 0;
                GetPassword(pass);
                if (CheckUserNameNotBan(username) == true)
                {

                    printf("You are banned. Please try again later.");
                    printf("Enter 1 to go to the previous menu: ");
                    int menu;
                    scanf("%d", &menu);
                    if (menu == 1)
                        LoginMenu();
                }
                cou++;
                if (cou == 5)
                {
                    while (BanUserName(username) == false)
                    {
                    }
                    printf("Please try again 15 minutes later.");
                    printf("Enter 1 to go to the previous menu: ");
                    int menu;
                    scanf("%d", &menu);
                    if (menu == 1)
                        LoginMenu();
                }
            } while (CheckPasswordRight(username, pass) != true);
            printf("\nlog in completed successfully.");
            struct user userData = GetUserData(username);
            MainMenu(userData);
        }
        else
        {
            printf("There is no user with this username.\n");
            LoginMenu();
        }
    }
}

void IncomeMenu(struct user logged)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%d. %s \n", i + 1, INCOME_MENU[i]);
    }
    int choice;
    do
    {
        printf(">>>please enter your choice: ");
        scanf("%d", &choice);
    } while (choice >= 1 && choice <= 8);

    struct income *temp = (struct income *)malloc(sizeof(struct income));
    temp = ReadInCome(logged.userName);
    struct income *filter = (struct income *)malloc(sizeof(struct income));

    if (choice == 1)
    {
        int totalIncome = SumIncome(temp);
        printf("Your total income is %d units.\n", totalIncome);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            IncomeMenu(logged);
    }
    else if (choice ==2)
    {
        struct date start;
        printf("Interval start time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &start.year, &start.month, &start.day);
        clear();
        struct date end;
        printf("Interval end time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &end.year, &end.month, &end.day);
        clear();
        int source;
        printf("source of income: ");
        scanf("%d", &source);
        filter = FilterIncome(start , end, source, temp);
        int totalIncome = SumIncome(filter);
        printf("The total %s income in the specified range is %d units.\n", INCOME_SOURCE[source+1], totalIncome);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            IncomeMenu(logged);
    }
    else if (choice == 3)
    {
        int maxIncome = SumIncome(temp);
        printf("Your maximum income is %d units.\n", maxIncome);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            IncomeMenu(logged);
    }
    else if (choice == 4)
    {
        struct date start;
        printf("Interval start time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &start.year, &start.month, &start.day);
        clear();
        struct date end;
        printf("Interval end time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &end.year, &end.month, &end.day);
        clear();
        int source;
        printf("source of income: ");
        scanf("%d", &source);
        filter = FilterIncome(start , end, source, temp);
        int maxIncome = SumIncome(filter);
        printf("The maximum %s income in the specified range is %d units\n", INCOME_SOURCE[source+1], maxIncome);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            IncomeMenu(logged);
    }
    else if (choice == 5)
    {
        RatioIncome(temp);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            IncomeMenu(logged);
    }
    else if(choice == 6)
    {

    }
    else if(choice == 7)
    {
        struct date start;
        printf("Interval start time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &start.year, &start.month, &start.day);
        clear();
        struct date end;
        printf("Interval end time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &end.year, &end.month, &end.day);
        clear();
        int source;
        printf("source of income: ");
        scanf("%d", &source);
        filter = FilterIncome(start , end, source, temp);
        int totalIncomeCertain = SumIncome(filter);
        printf("Your revenue from the %s field is %d units\n", INCOME_SOURCE[source+1], totalIncomeCertain);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            IncomeMenu(logged);
    }
    else if (choice == 8)
    {
        char word[NUM];
        printf("Enter the word you want to search: ");
        gets(word);
        struct income *searchWord = (struct income *)malloc(sizeof(struct income));
        searchWord = SearchIncome(word, temp);
        while (searchWord != NULL)
        {
            printf("%s => %d\n", searchWord->description, searchWord->price);
            printf("****************************************");
            searchWord = searchWord->next;
        }
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            IncomeMenu(logged);
    }
    else if(choice == 9)
    {
        //back to main menu
    }
}

void CostMenu(struct user logged)
{
    for (int i = 0; i < 9; i++)
    {
        printf("%d. %s \n", i + 1, COST_MENU[i]);
    }
    int choice;
    do
    {
        printf(">>>please enter your choice: ");
        scanf("%d", &choice);
    } while (choice >= 1 && choice <= 9);
    struct cost *temp = (struct cost *)malloc(sizeof(struct cost));
    temp = ReadCost(logged.userName);
    struct cost *filter = (struct cost *)malloc(sizeof(struct cost));

    if (choice == 1)
    {
        int totalcost = SumCost(temp);
        printf("Your total cost is %d units.\n", totalcost);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            CostMenu(logged);
    }
    else if (choice ==2)
    {
        struct date start;
        printf("Interval start time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &start.year, &start.month, &start.day);
        clear();
        struct date end;
        printf("Interval end time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &end.year, &end.month, &end.day);
        clear();
        int source;
        printf("source of cost: ");
        scanf("%d", &source);
        filter = FilterCost(start , end, source, temp);
        int totalCost = SumCost(filter);
        printf("The total %s cost in the specified range is %d units.\n", COST_SOURCE[source+1], totalCost);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            CostMenu(logged);
    }
    else if (choice == 3)
    {
        int maxCost = SumCost(temp);
        printf("Your maximum cost is %d units.\n", maxCost);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            CostMenu(logged);
    }
    else if (choice == 4)
    {
        struct date start;
        printf("Interval start time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &start.year, &start.month, &start.day);
        clear();
        struct date end;
        printf("Interval end time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &end.year, &end.month, &end.day);
        clear();
        int source;
        printf("source of cost: ");
        scanf("%d", &source);
        filter = FilterCost(start , end, source, temp);
        int maxCost = SumCost(filter);
        printf("The maximum %s cost in the specified range is %d units\n", COST_SOURCE[source+1], maxCost);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            CostMenu(logged);
    }
    else if (choice == 5)
    {
        RatioCost(temp);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            CostMenu(logged);
    }
    else if(choice == 6)
    {

    }
    else if(choice == 7)
    {
        struct date start;
        printf("Interval start time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &start.year, &start.month, &start.day);
        clear();
        struct date end;
        printf("Interval end time (yyyy/mm/dd): ");
        scanf("%d%*c%d%*c%d", &end.year, &end.month, &end.day);
        clear();
        int source;
        printf("source of cost: ");
        scanf("%d", &source);
        filter = FilterCost(start , end, source, temp);
        int totalCostCertain = SumCost(filter);
        printf("Your revenue from the %s field is %d units\n", COST_SOURCE[source+1], totalCostCertain);
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            CostMenu(logged);
    }
    else if (choice == 8)
    {
        char word[NUM];
        printf("Enter the word you want to search: ");
        gets(word);
        struct cost *searchWord = (struct cost *)malloc(sizeof(struct cost));
        searchWord = SearchCost(word, temp);
        while (searchWord != NULL)
        {
            printf("%s => %d\n", searchWord->description, searchWord->price);
            printf("****************************************");
            searchWord = searchWord->next;
        }
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            CostMenu(logged);
    }
    else if (choice == 9)
    {
        //back to main
    }

}

void MainMenu(struct user logged)
{
    for (int i = 0; i < 6; i++)
    {
        printf("%d. %s \n", i + 1, MAIN_MENU[i]);
    }
    int choice;
    do
    {
        printf(">>>please enter your choice: ");
        scanf("%d", &choice);
    } while (choice >= 1 && choice <= 6);

    if (choice == 1)
    {
        struct income newIncome = ReadNewInComeData();
        bool incomeTest = AddInCome(newIncome, logged);
        if (incomeTest == true)
            printf("Successfully registered.");
        else
            printf("Failed to register.");
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            MainMenu(logged);
    }

    else if (choice == 2)
    {
        struct cost newCost = ReadNewCostData();
        bool costTest = AddCost(newCost, logged);
        if (costTest == true)
            printf("Successfully registered.");
        else
            printf("Failed to register.");
        printf("Enter 1 to go to the previous menu: ");
        int menu;
        scanf("%d", &menu);
        if (menu == 1)
            MainMenu(logged);
    }

    else if (choice == 3)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("%d. %s \n", i + 1, STATISTICS[i]);
        }
        int choice;
        do
        {
            printf(">>>please enter your choice: ");
            scanf("%d", &choice);
        } while (choice >= 1 && choice <= 3);

        if (choice == 1)
        {
            IncomeMenu(logged);
        }

        else if (choice == 2)
        {
            CostMenu(logged);
        }
        else if (choice == 3)
        {
            int balanced = Balance(logged);
            printf("Your account balance is %d units.", balanced);
            printf("Enter 1 to go to the previous menu: ");
            int menu;
            scanf("%d", &menu);
            if (menu == 1)
                MainMenu(logged);
        }
    }

    else if (choice == 4)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("%d. %s \n", i + 1, SETTING[i]);
        }
        int choice;
        do
        {
            printf(">>>please enter your choice: ");
            scanf("%d", &choice);
        } while (choice >= 1 && choice <= 3);

        if (choice == 1)
            ChangePhone(logged);
        else if (choice == 2)
            ChangeEmail(logged);
        else
            ChangePassword(logged);
    }
    else if(choice == 4)
    {
        //sign out
    }

    else if (choice == 5)
    {
        //exit
    }
}

void main()
{
    struct user user1;
    user1.userIncomes = (struct income *)malloc(sizeof(struct income));
    user1.userIncomes->price = 1000;
    user1.userIncomes->next = NULL;
    struct cost come = ReadNewCostData();
    bool test = AddCostToLinkedList(come, user1);
    printf(">>>%d", test);
}
