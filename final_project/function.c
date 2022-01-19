#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define NUM 50


struct date{
    int year;
    int month;
    int day;
    struct date *next;
};
struct cost{
    int price;
    char source[NUM];
    char description[NUM];
    struct date *dates;
    struct cost *next;
};

struct income{
    int price;
    char source[NUM];
    char description[NUM];
    struct date *dates;
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
    struct income *userIncomes;
    struct cost *userCosts;
    struct user *next;
};

struct banUser{
    char userName[NUM];
    int time;
    struct banUser *next;
};

typedef enum { false = 0, true = 1 } bool;

char INCOME_SOURCE[4][50] = {"Programming rights !!!","Subsidy.","Family allowance money.","University!"};
char COST_SOURCE[7][50] = {"Clothing.","Travel.","Tuition fees.","Entertainment.", "Pay bills.", "Medical expenses.", "Charity help."};


void clear()
{
    int c;
    while((c=getchar())!= '\n'&& c!= EOF){}
}


bool VerifyNcode(char nCode[])
{
    int len = 10, i;
    bool result = true;
    if (strlen(nCode) == len)
    {
        for(i=0; i<len ;i++)
        {
            if (isdigit(nCode[i])!= 1)
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
        if(phone[0]=='0' && phone[1]=='9')
        {
            for(i=0; i<len; i++)
            {
                if (isdigit(phone[i])!= 1)
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
    int len = 10, i=0, digit=0, alpha=0, character=0;
    bool result = true;

    if (strlen(pass)>= len)
    {
        while(pass[i] != '\0')
        {
            if(pass[i]== '%' || pass[i] == '@' || pass[i] == '*')
                character++;
            else if (isdigit(pass[i]) == 1 )
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
    int len = 15, i=0;
    bool result = false;

    if (strlen(email) >= len)
    {
        while(email[i] != '\0')
        {
            if(email[i] == '@')
            {
                result =true;
                break;
            }
            i++;
        }
    }
    return result;
}

bool VerifyUserName(char userName[])
{
    int len = 8, i=0;
    bool result = true;

    if (strlen(userName) >= len)
    {
        while(userName[i] != '\0')
        {
            if((userName[i]>='a' && userName[i]<='z')||(userName[i]>='A' && userName[i]<='Z') ||
                (userName[i]>='0' && userName[i]<='9'))
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
    bool result = true;
    if((VerifyNcode(users.nCode) == true) && (VerifyPhone(users.phone) == true) && (VerifyPassword(users.password) == true) &&
        (VerifyEmail(users.email) == true) && (VerifyUserName(users.userName)== true))
        result = true;
    else
        result = false;

    return result;
}

struct user GetSignUpData()
{
    struct user users;
    char passVr[NUM];
    printf("first name: ");
    gets(users.firstName);
    clear();
    printf("\nlast name: ");
    gets(users.lastName);
    clear();
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
    do{
        printf("\npassword: ");
        scanf("%s", users.password);
        clear();
        printf("\nPassword verification: ");
        scanf("%s", passVr);
        clear();
    }while(strcmp(users.password, passVr)!=0);

    return users;
}

bool AddNewUser(struct user users)
{
    char name = users.userName, address[50] = "/users/";
    strcat(name, ".txt");
    strcat(address, name);

    bool result = true;
    int test;
    FILE *fp;
    fp = fopen(address, "w+");
    if (fp == NULL)
    {
        printf("file could not be opened!!");
        result = false;
    }
    else
    {
        test = fwrite(&users, sizeof(struct user), 1, fp);
        if(test != 1)
               result = false;
    }
    fclose(fp);
    return result;
}


void GetUserName(char* userName)
{
    printf("please enter your user name: ");
    scanf("%s", userName);
    clear();
}

bool CheckUserNameExist(char userNames[])
{
    struct user users;
    char name = users.userName, address = "/users/";
    strcat(name, ".txt");
    strcat(address, name);
    bool result = false;
    int i;
    FILE *fp;
    fp = fopen(address, "r");
    if (fp == NULL)
        printf("file could not be opened!!");
    else
    {
        fread(&users, sizeof(struct user), 1, fp);
        if (strcmp(users.userName, userNames) == 0)
            result = true;
    }
    fclose(fp);
    return result;
}

bool BanUserName(char userName[])
{
    bool result = true;
    int test;
    struct banUser newBanUser;
    strcpy(newBanUser.userName, userName);
    newBanUser.time = time(NULL);

    FILE * fp;
    fp = fopen("banUser.txt", "a+");
    if (fp == NULL)
        result = false;
    else
    {
        test = fwrite(&newBanUser, sizeof(struct banUser), 1, fp);
        if(test != 1)
        {
            struct banUser *curr, *latter, *head;
            head = (struct banUser*)malloc(sizeof(struct banUser));

            if(head==NULL){

                head->time = newBanUser.time;
                strcpy(head->userName, newBanUser.userName);
                head->next = NULL;
                curr = head;
            }
            else{
                while(curr->next != NULL)
                {
                    curr = curr->next;
                }
                    
                latter = (struct banUser*)malloc(sizeof(struct banUser));

                latter->time = newBanUser.time;
                strcpy(latter->userName, newBanUser.userName);
                curr->next = latter;
                curr = latter;
            }
            result = false;
        }         
    }
    fclose(fp);
    return result;
}


bool CheckUserNameNotBan(char userName[])
{
    bool result = false;
    struct banUser banUsers;
    int timer = time(NULL);
    
    FILE *fp;
    fp = fopen("banUser.txt", "r");
    if (fp == NULL)
        printf("file could not be opened!!");
    else
    {
        fread(&banUsers, sizeof(struct banUser), 8, fp);
        
        struct banUser *temp, *head;
        temp = head;
        do{
            if (strcmp(banUsers.userName, userName) == 0)
            {
                //check time
                result = true;
                break;
            }
            temp = temp->next;

        }while(temp != NULL);
        
        
        
    }
    fclose(fp);
    return result;
}


void GetPassword(char *pass)
{
    printf("please enter your password: ");
    scanf("%s", pass);
    clear();
}


bool CheckPasswordRight(char userName[], char password[])
{
    bool result = true;
    int i;
    struct user users;
    char name = users.userName, address[50] = "/users/";
    strcat(name, ".txt");
    strcat(address, name);

    FILE *fp;
    fp = fopen(address, "r");
    if (fp == NULL)
        result = false;
    else
    {
        fread(&users, sizeof(struct user), 1, fp);
        if (strcmp(users.userName, userName)==0)
        {
            if (strcmp(users.password, password)!=0)
                result = false;
        }
        else
            result = false;

    }
    fclose(fp);
    return result;
}





struct income * ReadInCome(char username[])
{
    bool result = true;
    int test;
    struct user users;
    char name = users.userName, address[50] = "/income/";
    strcat(name, ".txt");
    strcat(address, name);
    struct income *head;
    FILE *fp;
    fp = fopen(name, "r");
    if (fp == NULL)
        result = false;

    else
    {
        struct income temp;
        fread(&temp, sizeof(struct income), 1, fp);

        head = malloc(sizeof(struct income));
        head->price = temp.price;
        strcpy(head->source, temp.source);
        head->dates->year = temp.dates->year;
        head->dates->month = temp.dates->month;
        head->dates->day = temp.dates->day;
        strcpy(head->description, temp.description);

        head->next = NULL;
    }
    fclose(fp);

    return head;
}


struct cost* ReadCost(char username[])
{
    bool result = true;
    int test;
    struct user users;
    char name = users.userName, address[50] = "/cost/";
    strcat(name, ".txt");
    strcat(address, name);
    struct cost *head;
    FILE *fp;
    fp = fopen(name, "r");
    if (fp == NULL)
        result = false;
    else
    {
        struct cost temp;
        fread(&temp, sizeof(struct cost), 1, fp);

        head = malloc(sizeof(struct cost));

        head->price = temp.price;
        strcpy(head->source, temp.source);
        head->dates->year = temp.dates->year;
        head->dates->month = temp.dates->month;
        head->dates->day = temp.dates->day;
        strcpy(head->description, temp.description);

        head->next = NULL;
    }
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

    printf("Income amount: ");
    scanf("%d", &newIncome.price);
    clear();
    printf("\nIncome source number: \n");
    printf("1. Programming rights !!!\n2. Subsidy.\n3. Family allowance money.\n4. University Scholarship!\n");
    printf("please enter your choice: ");
    scanf("%d", &newIncome.source);
    clear();
    printf("\nIncome Date (yyyy/mm/dd): ");
    scanf("%d%*c%d%*c%d", &newIncome.dates->year, &newIncome.dates->month, &newIncome.dates->day);
    clear();
    printf("Description (within one line): ");
    gets(newIncome.description);
    clear();

    return newIncome;
}

bool AddInComeToFile(struct income incomes, struct user uses)
{
    bool result = true;
    int test;
    struct user users;
    char name = users.userName, address[50] = "/income/";
    strcat(name, ".txt");
    strcat(address, name);

    FILE *fp;
    fp = fopen(name, "a+");
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



bool AddInComeToLinkedList(struct income newIncome, struct user user)
{
    struct user *head;
    struct income *headIncome = (struct income*)malloc(sizeof(struct income));
    
    headIncome->price = newIncome.price;
    strcpy(headIncome->source, newIncome.source);
    headIncome->dates = malloc(sizeof(struct date));
    headIncome->dates->year = newIncome.dates->year;
    headIncome->dates->month = newIncome.dates->month;
    headIncome->dates->day = newIncome.dates->day;
    strcpy(headIncome->description, newIncome.description);
    headIncome->next = NULL;
    headIncome->dates->next = NULL;

    if(head->userIncomes == NULL)
    {
        head->userIncomes = headIncome;
    }
    else
    {
        struct income *curr;
        while(curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = headIncome;
    }
        
    
    return true;
}



bool AddInCome(struct income incomes, struct user uses)
{
    bool result = false;
    if(AddInComeToLinkedList(incomes, uses) == 1 &&
        AddInComeToFile(incomes, uses) == 1)
        {
            result = true;
        }
    return result;
}



struct cost ReadNewCostData()
{
    struct cost newCost;

    printf("Amount of expenses: ");
    scanf("%d", &newCost.price);
    clear();
    printf("\nCost item: \n");
    printf("1. Clothing\n2. Travel\n3. Tuition fees\n4. Entertainment\n5. Pay bills\n6. Medical expenses\n7. Charity help\n");
    printf("please enter your choice: ");
    scanf("%d", &newCost.source);
    clear();
    printf("\nCost Date (yyyy/mm/dd): ");
    scanf("%d%*c%d%*c%d", &newCost.dates->year, &newCost.dates->month, &newCost.dates->day);
    clear();
    printf("Description (within one line): ");
    gets(newCost.description);
    clear();

    return newCost;
}


bool AddCostToFile(struct cost costs, struct user uses)
{
    bool result = true;
    int test;
    struct user users;
    char name = users.userName, address[50] = "/cost/";
    strcat(name, ".txt");
    strcat(address, name);

    FILE *fp;
    fp = fopen(name, "a+");
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
    struct cost *curr, *latter, *head;
    head = (struct cost*)malloc(sizeof(struct cost));

    if(head==NULL){
	    head->price = newCost.price;
	    strcpy(head->source, newCost.source);
        head->dates = malloc(sizeof(struct date));
	    head->dates->year = newCost.dates->year;
	    head->dates->month = newCost.dates->month;
	    head->dates->day = newCost.dates->day;
	    strcpy(head->description, newCost.description);
        head->next = NULL;
        curr = head;
    }
    else{
	    while(curr->next != NULL)
        {
            curr = curr->next;
        }
	    	
	    latter = (struct cost*)malloc(sizeof(struct cost));

	    latter->price = newCost.price;
	    strcpy(latter->source, newCost.source);
        latter->dates = malloc(sizeof(struct date));
	    latter->dates->year = newCost.dates->year;
	    latter->dates->month = newCost.dates->month;
	    latter->dates->day = newCost.dates->day;
	    latter->next = NULL;
	    strcpy(latter->description, newCost.description);

	    curr->next = latter;
	    curr = latter;
	}


    return true;
}


bool AddCost(struct cost costs, struct user uses)
{
    bool result = false;
    if(AddCostToLinkedList(costs, uses) &&
        AddCostToFile(costs, uses))
        {
            result = true;
        }
    return result;
}




void ChangePassword(struct user users)
{
    char password[NUM], newPass[NUM], newPassVr[NUM];
    printf("Current password: ");
    scanf("%s", password);

    if(CheckPasswordRight(users.userName, password) == 1)
    {
        do{
            printf("\nnew password: ");
            scanf("%s", newPass);

            printf("\nnew Password verification: ");
            scanf("%s", newPassVr);

        }while(strcmp(newPass, newPassVr)!=0 && VerifyPassword(newPass) == 0 && VerifyPassword(newPassVr) == 0);
        strcpy(users.password, newPass);

        AddNewUser(users);
    }

}


void ChangeEmail(struct user users)
{

    char email[NUM], newEmail[NUM];
    printf("Current email: ");
    scanf("%s", email);

    if(strcmp(users.email, email)==0)
    {
        printf("\nnew email: ");
        scanf("%s", newEmail);
        if(VerifyEmail(newEmail) == 1)
            strcpy(users.email, newEmail);

        AddNewUser(users);
    }

}


void ChangePhone(struct user users)
{
    char phone[NUM], newPhone[NUM];
    printf("Current phone number: ");
    scanf("%s", phone);

    if(strcmp(users.phone, phone) == 0)
    {
        printf("\nnew phone number: ");
        scanf("%s", newPhone);
        if(VerifyPhone(newPhone) == 1)
            strcpy(users.phone, newPhone);

        AddNewUser(users);
    }
}

void main()
{

    struct cost test= ReadNewCostData();
    int resultOf ;
}


