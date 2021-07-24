#include<stdio.h>
#include<string.h>
#define len 10
char curr[][len]  = {"INR", "AUS", "SGP", "EURO", "POUND", "USD"};
float rates_to_comm [len] = {72.812, 1.289, 1.40, 0.813, 0.705, 1.00};
float cur_conv(float, char [], char[]);
int main()
{
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
	return 0;
}
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
	common = from_value/from_rate;
	fin = common*to_rate;
	return fin;
}


