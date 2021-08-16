#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define len 10
int from_c,to_c,enteredAmount;
char curr[][len]  = {"INR", "AUS", "SGP", "EURO", "POUND", "USD"};
float rates_to_comm [len] = {72.812, 1.289, 1.40, 0.813, 0.705, 1.00};
///SOME FEATURES WE CAN FURTHER IMPLEMENT
///[DONE]A function to convert from one currency
///A function to add a new currency and its rate 
///A function to delete a type of currency
///A base convertor function
///A soon as a user enters the currency value we convert it to a base value and then we navigate the program using that base value 
///We store the currencies in a linked list 
///Makes adding and deleting easier
///we declared entered data as global can be acessed from anywhere 
void display()
{
    
}

struct currency
{
    char  name[40];
    float rate;

};

float cur_conv(float from_value, char from_curr[], char to_curr[])
{
	float from_rate, to_rate, fin, common;
	for(int i = 0;i < len; i++)
	{
		if(strcmp(from_curr, curr[i]) == 0){
			from_rate = rates_to_comm[i];
		}
	}
	for(int j = 0;j<len;j++){
		if(strcmp(to_curr, curr[j]) == 0)
		{
		to_rate = rates_to_comm[j];
	    }
	}
	printf("\n %f %f", from_rate, to_rate);
	common = from_value/from_rate;
	printf("\n%f", common);
	fin = common*to_rate;
	printf("\n%f", fin);
	return fin;
}

void info()
{
    int choice;
    bool flag=true;
    while(flag)
    {
        printf("Enter the action you want to perform: \n");
        printf("1. Compare currencies:\n");
        printf("2. Add a new currency to existing list:\n");
        printf("3. Delete a currency from the given list:\n");
        printf("4. Display list of currencies avaliable: \n");
        printf("5. Modify currency value: \n");
        printf("6. Exit function:");
        switch(choice)
        {
            case 1:
                    ///DISPLAY LIST OF AVAILABLE CURRENCIES

                    ////CALL COMPARE CURRENCY FUNCTION
                    ///currency compare function returns a float value
                    ///it takes in 3 parameters
                    ///a character array which is the currency entered 
                    //the amount in the currency entered 
                    ///another character array which is the currency to be converted into
                    float from_v, to_v;
                    char from_c[100], to_c[100];
                    printf("Enter the currency you would like to convert : ");
                    gets(from_c);
                    printf("\nEnter the currency you would like to convert to: ");
                    gets(to_c);
                    printf("\nEnter the amount of money you have right now : ");
                    scanf("\n%f", &from_v);
                    to_v = cur_conv(from_v, from_c, to_c);
                    printf("\nThe amount in %s is %f", to_c, to_v);
                    break;
            case 2:
                    ////Call add currency function and add to a linked list
                    printf("NOT READY\n");
                    break;
            case 3:
                    ////Call delete currency function and delete from list
                    printf("NOT READY\n");
                    break;
            case 4:
                    ////Call display currency function
                    printf("NOT READY\n");
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
void converter(struct currency c)
{

}


int main(void)
{
 info();
 return 0;
}
