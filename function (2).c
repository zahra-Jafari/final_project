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
};
struct cost{
    int price;
    char scource[NUM];
    char description[NUM];
    struct date dates;
    struct cost *next;
};

struct income{
    int price;
    char scource[NUM];
    char description[NUM];
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
    struct income userIncomes;
    struct cost userCosts;
    struct user *next;
};

struct banUser{
    char userNeme[NUM];
    int hour;
    int min;
    int seconds;
    struct banUser *next;
};

typedef enum { false = 0, true = 1 } bool;
//1. Programming rights !!!\n2. Subsidy.\n3. Family allowance money.\n4. University Scholarship!
char INCOME_SOURCE[4][50] = {"Programming rights !!!","Subsidy.","Family allowance money.","University!"};

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
    struct banUser banUsers;
    strcpy(banUsers.userNeme, userName);
    int timer = time(NULL);

    banUsers.seconds = (time(NULL)%60);
    banUsers.min = (time(NULL)%3600)/60;
    banUsers.hour = time(NULL)/3600;

    FILE * fp;
    fp = fopen("banUser.txt", "a+");
    if (fp == NULL)
        result = false;
    else
    {
        test = fwrite(&banUsers, sizeof(struct banUser), 1, fp);
        if(test != 1)
               result = false;
    }
    fclose(fp);
    return result;
}


bool CheckUserNameNotBan(char userName[])
{
    bool result = false;
    struct banUser banUsers[8];
    int timer = time(NULL), hour, min, seconds;
    seconds = (time(NULL)%60);
    min = (time(NULL)%3600)/60;
    hour = time(NULL)/3600;
    int i;
    FILE *fp;
    fp = fopen("banUser.txt", "r");
    if (fp == NULL)
        printf("file could not be opened!!");
    else
    {
        fread(&banUsers, sizeof(struct banUser), 8, fp);
        for(i=0;i<8;i++)
        {

            if (strcmp(banUsers[i].userNeme, userName) == 0)
            {
                //check time
                result = true;
                break;
            }
        }
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





struct income * ReadInComes(char username[])
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
        strcpy(head->scource, temp.scource);
        head->dates.year = temp.dates.year;
        head->dates.month = temp.dates.month;
        head->dates.day = temp.dates.day;
        strcpy(head->description, temp.description);
        head->next = NULL;
    }
    fclose(fp);

    return head;
}


struct cost* ReadCosts(char username[])
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
        strcpy(head->scource, temp.scource);
        head->dates.year = temp.dates.year;
        head->dates.month = temp.dates.month;
        head->dates.day = temp.dates.day;
        strcpy(head->description, temp.description);

        head->next = NULL;
    }
    return head;
}



struct income ReadNewInComeData()
{
    struct income newIncome;
	int IDInComeSource;
    printf("Income amount: ");
    scanf("%d", &newIncome.price);
    clear();
    printf("\nIncome source number: \n");
    for(int i;i<4;i++){
    	printf("%d. %s \n",i+1,INCOME_SOURCE[i]);
	}
    printf("please enter your choice: ");
    scanf("%d", &IDInComeSource);
    printf("%d",IDInComeSource-1);
    printf("%s",INCOME_SOURCE[IDInComeSource-1]);
    clear();
    strcpy(newIncome.scource,INCOME_SOURCE[IDInComeSource-1]);
    printf("\nIncome Date (yyyy/mm/dd): ");
    scanf("%d%*c%d%*c%d", &newIncome.dates.year, &newIncome.dates.month, &newIncome.dates.day);
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

    struct income *curr, *latt;
    curr = &user.userIncomes;
    if(curr == NULL){
    	user->userIncomes = malloc(sizeof(struct income));
    	latt = user.userIncomes;
    	latt = malloc(sizeof(struct income));

	    latt->price = newIncome.price;
	    strcpy(latt->scource, newIncome.scource);
	    latt->dates.year = newIncome.dates.year;
	    latt->dates.month = newIncome.dates.month;
	    latt->dates.day = newIncome.dates.day;
	    latt->next = NULL;
	    strcpy(latt->description, newIncome.description);
    }
    else{
	    while(curr->next != NULL){
	    	curr = curr->next
		}
	    latt = malloc(sizeof(struct income));

	    latt->price = newIncome.price;
	    strcpy(latt->scource, newIncome.scource);
	    latt->dates.year = newIncome.dates.year;
	    latt->dates.month = newIncome.dates.month;
	    latt->dates.day = newIncome.dates.day;
	    latt->next = NULL;
	    strcpy(latt->description, newIncome.description);

	    curr->next = latt;
	    curr = latt;
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
    scanf("%d", &newCost.scource);
    clear();
    printf("\nCost Date (yyyy/mm/dd): ");
    scanf("%d%*c%d%*c%d", &newCost.dates.year, &newCost.dates.month, &newCost.dates.day);
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
    struct cost *curr, *latt;
    curr = malloc(sizeof(struct cost));
    latt = malloc(sizeof(struct cost));

    latt->price = newCost.price;
    strcpy(latt->scource, newCost.scource);
    latt->dates.year = newCost.dates.year;
    latt->dates.month = newCost.dates.month;
    latt->dates.day = newCost.dates.day;
    strcpy(latt->description, newCost.description);

    curr->next = latt;
    curr = latt;

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
	struct income temp;
 	temp=ReadNewInComeData();
 	printf("%d %s %s",temp.price,temp.description,temp.scource);
}



