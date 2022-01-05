#include<stdio.h>
#include<ctype.h>
#include<string.h>

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
};


typedef enum { false = 0, true = 1 } bool;

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
            if((userName[i]>='a' && userName[i]<='z')||(userName[i]>='A' && userName[i]<='Z') || (userName[i]>='0' && userName[i]<='9'))
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
    if((VerifyNcode(users.nCode) == true) && (VerifyPhone(users.phone) == true) && (VerifyPassword(users.password) == true) && (VerifyEmail(users.email) == true) && (VerifyUserName(users.userName)== true))
        result = true;
    else
        result = false;

    return result;
}

struct user GetSignUpData(void)
{
    struct user users;

    printf("first name: ");
    scanf("%s", &users.firstName);
    printf("\nlast name: ");
    scanf("%s", &users.lastName);
    printf("\nuser name: ");
    scanf("%s", &users.userName);
    printf("\nnational code: ");
    scanf("%s", &users.nCode);
    printf("\nphone number: ");
    scanf("%s", &users.phone);
    printf("\nemail address: ");
    scanf("%s", &users.email);
    do{
        printf("\npassword: ");
        scanf("%s", &users.password);
        printf("\nPassword verification: ");
        scanf("%s", &users.passwordVerification);
    }while(strcmp(user.password, user.passwordVerification)!=0)

    return users;
}

char GetUserName(void)
{
    char userName[NUM];
    printf("please enter your user name: ");
    scanf("%s", &userName);

    return userName;
}

bool CheckUserNameExist(char userName[])
{
    bool result = false;
    for(i=0;i<100;i++)
        if (strcmp(user.userName, userName)==0)
            result = true;

    return result;
}

char GetPassword(void)
{
    char password[NUM];
    printf("please enter your password: ");
    scanf("%s", &password);

    return password;
}

bool CheckPasswordRight(char userName[], char password[])
{
    bool result = false;
    for(i=0;i<100;i++)
        if (strcmp(user.userName, userName)==0)
            if (strcmp(user.password, password)==0)
                result = true;

    return result;
}




