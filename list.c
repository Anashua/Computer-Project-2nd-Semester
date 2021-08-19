#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
struct currency
{
    char  name[40];
    float rate;

};
struct node
{
    struct currency currency;
    struct node* link;
};
struct mylist
{
    struct node* head;
};
void fileList();
void initialise(struct mylist*);
void display(struct mylist*);
void insert(struct mylist*,struct currency);
struct currency addCurr();
void displayCurr(struct currency);
void addNew();
void addCSV();
void modCurr();
void modCSV(char*,int);
void delCurr();
void delCSV(char*);
void info();
void searchCurr();
void currConvertMenu();
float currConv(char c1[], char c2[], struct node* n,int c, struct currency cur);

///STATIC  VARIABLES
static struct mylist list;
static int len=0;
///MAIN
int main()
{
    //This function must be the first one to be called 
    fileList();
    info();
    return 0;
}
///INITIALISE LIST
void initialise(struct mylist* l)
{
    l->head=NULL;
}
///DISPLAYS EVERYTHING IN THE LIST
void display(struct mylist* l)
{
    struct node* traverse=l->head;
    if(traverse==NULL)
        printf("\nNO CURRENCIES IN LIST\n");
    else
    {
        printf("\nThe currencies in the list are:\n");
        while(traverse!=NULL)
        {
            displayCurr(traverse->currency);
            traverse=traverse->link;
        }
    }
}
///INSERTS STUFF TO THE LIST
void insert(struct mylist* l,struct currency data)
{
    struct node* temp=(struct node*) malloc(sizeof(struct node));
    strcpy(temp->currency.name,data.name);
    temp->currency.rate=data.rate;
    temp->link=NULL;
    if(l->head==NULL)
    {
        l->head=temp;
    }
    else
    {
        struct node* present=l->head;
        struct node* previous=NULL;
        while(present!=NULL && strcmp(present->currency.name,data.name)<0)
        {
            previous=present;
            present=present->link;
        }
        if(previous==NULL)
        {
            temp->link=present;
            l->head=temp;
        }
        else
        {
            temp->link=present;
            previous->link=temp;
        }
    }
}
///ADD A NEW CURRENCY
struct currency addCurr()
{
    struct currency cur;
    printf("\nEnter the name of the currency: ");
    scanf("%[^\n]",cur.name);
    printf("\nEnter its exchange rate in INR: ");
    scanf("%f%c",&cur.rate);
    return cur;
}
///DISPLAYS A SINGLE CURRENCY
void displayCurr(struct currency cur)
{
    printf("\n%s : %f \n",cur.name,cur.rate);
}
void info()
{
    int choice;
    bool flag=true;
    while(flag)
    {
        printf("\nEnter the action you want to perform: \n");
        printf("\n1. Currency convertor:\n");
        printf("\n2. Add a new currency to existing list:\n");
        printf("\n3. Delete a currency from the given list:\n");
        printf("\n4. Display list of currencies avaliable: \n");
        printf("\n5. Modify currency value: \n");
        printf("\n6. Search for currency details:\n");
        printf("\n7. Exit function:\n");
        scanf("%d%c",&choice);
        switch(choice)
        {
            case 1:
                    currConvertMenu();
                    break;
            case 2:
                    addNew();
                    break;
            case 3:
                    ////Call delete currency function and delete from list
                    delCurr();
                    break;
            case 4:
                    ////Call display currency function
                    display(&list);
                    break;
            case 5:
                    modCurr();
                    break;
            case 6:
                    //FUNCTION TO SEARCH A Currency will print details of that currency
                    searchCurr();
                    
                    break;
            case 7:
                   flag=false;
        } 
    }
    printf("\nThankyou for using currency convertor");
}
void fileList()
{
    FILE *fp=fopen("currencies.csv","r");
    char str[500];
    
    while(!feof(fp))
    {
        fgets(str,100,fp);
        len++;
    }
    rewind(fp);
    for(int i=0;i<len;i++)
    {
        fgets(str,100,fp);
        struct currency cur;
        char *temp=strtok(str,",");
        strcpy(cur.name,temp);
        temp=strtok(NULL,",");
        cur.rate=atof(temp);
        insert(&list,cur);
    }
}
void addNew()
{
    printf("\nEnter data for a new curency\n");
    struct currency data;
    data=addCurr();
    insert(&list,data);
    int ch;
    printf("Do you want to save currency to memory: (1->Yes/0->No) : ");
    scanf("%d%c",&ch);
    if(ch==1)
    {
        addCSV(data);
    }
   
}
//ADDS A CURRENCY TO THE CSV FILE 
void addCSV(struct currency cur)
{
    FILE *fp=fopen("currencies.csv","a+");
    if(fp!=NULL)
    {
        fputc('\n',fp);
        fputs(cur.name,fp);
        fprintf(fp,",%f",cur.rate);
    }  
    fclose(fp); 
}
void modCurr()
{
    printf("Enter the name of the currency to be modified : ");
    char modify[40];
    gets(modify);
    int new;
    struct node *traverse=list.head;
    if(traverse==NULL)
        printf("\nNO CURRENCIES IN LIST\n");
    else
    {
        while(traverse!=NULL)
        {
            if(strcmp(traverse->currency.name,modify)==0)
            {
                printf("\nEnter the new rate : ");
                scanf("%d%c",&new);
                traverse->currency.rate=new;
            }
            traverse=traverse->link;
        }
    }
    printf("\nDo you wish to delete currency data permanently from memory? (1->Yes\0->No) : ");
    int cho;
    scanf("%d%c",&cho);
    if(cho==1)
    {
        modCSV(modify,new);
    }
    return;
}
void modCSV(char *name,int new)
{
    FILE *fp=fopen("currencies.csv","r");
    FILE *fp1=fopen("temp.csv","w");
    char str[100];
    for(int i=0;i<len;i++)
    {
        fgets(str,100,fp);
        char copy[100];
        strcpy(copy,str);
        char *temp=strtok(copy,",");
        if(strcmp(temp,name)!=0)
        {
            fputs(str,fp1);
        }
        else
        {
            char buff[50];
            snprintf(buff,50,"%s,%d\n",temp,new);
            fputs(buff,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("currencies.csv");
    rename("temp.csv","currencies.csv");
}
void delCurr()
{
    printf("Enter the name of the currency to be deleted: ");
    char modify[40];
    gets(modify);
     struct node *traverse=list.head;
     struct node *previous=NULL;
    if(traverse==NULL)
        printf("\nNO CURRENCIES IN LIST\n");
    else
    {
        while(traverse!=NULL)
        {
            if(strcmp(traverse->currency.name,modify)==0)
            {
                struct node *temp=traverse;
                if(previous!=NULL)
                {
                    previous->link=temp->link;
                    free(temp);
                }
                else
                {
                    list.head=temp->link;
                    free(temp);
                }
                printf("\nDo you wish to delete currency data permanently from memory? (1->Yes\0->No) : ");
                int cho;
                scanf("%d%c",&cho);
                if(cho==1)
                {
                    delCSV(modify);
                }
                return;
            }
            else
            {
                previous=traverse;
                traverse=traverse->link;
            }
        }
        printf("\nCurrency not in list\n");
    }
    
}

void delCSV(char *name)
{
    FILE *fp=fopen("currencies.csv","r");
    FILE *fp1=fopen("temp.csv","w");
    char str[100];
    for(int i=0;i<len;i++)
    {
        fgets(str,100,fp);
        char copy[100];
        strcpy(copy,str);
        char *temp=strtok(copy,",");
        if(strcmp(temp,name)!=0)
        {
            fputs(str,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("currencies.csv");
    rename("temp.csv","currencies.csv");
}
void currConvertMenu()
{
    struct currency cur;
    struct node* n=list.head;
    printf("Would you like to add a currency or choose from the list given below?\nChoose an option");
    printf("\n1.Add a new currency: ");
    printf("\n2.Choose from the given list: ");
    int choice;
    scanf("%d%c", &choice);
    switch(choice){
    case 1:
        addNew();
    case 2:
        display(&list);
        printf("\nPlease enter your currency: ");
        char curr[40];
        gets(curr);
        int current;
        printf("Please enter the amount to convert : ");
        scanf("%d%c",&current);
        char curr2[40];
        printf("\nPlease enter the currency you would like to convert it to : ");
        gets(curr2);
        float converted;
        converted = currConv(curr,curr2, n,current, cur);
        printf("The value in the required currency is : %f ", converted);
        break;
    default:
        printf("\nInvalid choice.");
    }
}
float currConv(char c1[], char c2[], struct node* n,int c, struct currency cur)
{
    float rate1;
    float rate2;
    while(n!=NULL)
    {
           if(strcmp(c1,n->currency.name)==0){
                rate1 = n->currency.rate;
           }
           if(strcmp(c2,n->currency.name)==0){
                rate2 = n->currency.rate;
           }
           n=n->link;
    }
    float inr = c/rate1;
    float fin = inr*rate2;
    return fin;
}
void searchCurr()
{
    bool choice=false;
    printf("Enter the name of the currency to be searched");
    char name[100];
    gets(name);
    struct node* traverse=list.head;
    while(traverse!=NULL)
    {
        if(strcmp(traverse->currency.name,name)==0)
        {
            choice =true;
            printf("\nRequired currency values are :\n");
            displayCurr(traverse->currency);
        }
       traverse=traverse->link;
    }
    if(choice ==false)
    {
        printf("\nThe required currency is not present in list \n");
    }
}


