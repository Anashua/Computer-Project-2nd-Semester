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
void info();
static struct mylist list;
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
        while(present!=NULL && strcmp(present->currency.name,data.name)>0)
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
        printf("Enter the action you want to perform: \n");
        printf("1. Currency convertor:\n");
        printf("2. Add a new currency to existing list:\n");
        printf("3. Delete a currency from the given list:\n");
        printf("4. Display list of currencies avaliable: \n");
        printf("5. Modify currency value: \n");
        printf("6. Exit function:");
        scanf("%d%c",&choice);
        switch(choice)
        {
            case 1:
                    printf("\n*****************Currency convertor function********************\n");
                    break;
            case 2:
                    ////Call add currency function and add to a linked list
                    printf("\nEnter data for a new curency\n");
                    struct currency data;
                    data=addCurr();
                    insert(&list,data);
                    break;
            case 3:
                    ////Call delete currency function and delete from list
                    printf("NOT READY\n");
                    break;
            case 4:
                    ////Call display currency function
                    display(&list);
                    break;
            case 5:
                    printf("NOT READY\n");
                    break;
            case 6:
                   flag=false;
        }
        printf("Thankyou for using currency convertor :");
    }
}
void fileList()
{
    FILE *fp=fopen("currencies.csv","r");
    char str[500];
    int len=0;
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


