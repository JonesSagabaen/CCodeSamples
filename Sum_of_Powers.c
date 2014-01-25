/**************************************************************************************************
Jones Sagabaen
C Code Samples
This file is a part of a series of simple programs written in the C programming language.
Each program performs a simple function that requires user input.

Sum_of_Powers.c
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
/*
Class implements every method by using recursion.  No for loops or while loops are allowed.
The main() method is the only exception for the while loop.  The while loop is used as an infinite
loop to continually get the user's command until the user enters the "quit" commmand.
*/


/*
The wrapper method calls the helper method, power_helper() to calculate base n to 
power n.
*/
int power(n)
{
	return power_helper(n, n, n);
}

/*
The helper method for power() method.
*/
int power_helper(n, sum, count)
{
	if(count == 1)
		return sum;
	else
	{
		sum = sum * n;
		return power_helper(n, sum, count - 1);
	}
}

/*
The wrapper method calls the helper method, sum_of_powers_helper() to calculate base n to 
power n starting from value n and subsiquently decreasing n by 1 at each summand until the
value of n equals 1.
*/
int sum_of_powers(n)
{
	sum_of_powers_helper(n, 0, n);
}

/*
The helper method for sum_of_powers() method.
*/
int sum_of_powers_helper(n, sum, count)
{
	if(count == 0)
		return sum;
	else
	{
		sum = sum + power(count);
		return sum_of_powers_helper(n, sum, count - 1);
	}
}

/*
Main method gets the user's command and recognizes one of three options:
	quit, help, <n>
<n> is any positive value the user enters into the console.  The sum_of_powers() method will uses n
in its parameters and calculate base n to power n starting from value n and subsiquently decreasing
n by 1 at each summand until the value of n equals 1.
*/
int main()
{
	printf("Enter \"help\" for a list of commands\n");
	while(1)
	{
		char input[10];
		int valid_character = 0;
		int i;
		while(valid_character == 0)
		{
			printf("Please enter a command: ");
			fgets(input, 20, stdin);
			for(i = 0; i < strlen(input) - 1; i++)
			{
				if(input[i] == ' ')
					valid_character = 1;
				else if(input[i] >= 'a' && input[i] <= 'z')
				{
					input[i] = input[i] - 'a' + 'A';
					valid_character = 1;
				}
				else if(input[i] >= 'A' && input[i] <= 'Z' || input[i] >= '0' && input[i] <= '9')
					valid_character = 1;
				else
				{
					valid_character = 0;
					printf("\nYou entered an invalid entry!\n");
					printf("You entered an invalid character.\n\n");
					printf("Enter \"help\" for a list of commands\n");
					break;
				}
			}
		}
		//The user entered "quit"
		if(input[0] == 'Q' && input[1] == 'U' && input[2] == 'I' && input[3] == 'T')
		{
			printf("\n*******************************************************************************\n");
			printf("Thanks for using this sum of powers application!\n");
			printf("*******************************************************************************\n");
			return 0;
		}
		//The user entered "help"
		else if(input[0] == 'H' && input[1] == 'E' && input[2] == 'L' && input[3] == 'P')
		{
			printf("\n*******************************************************************************\n");
			printf("[quit]\n");
			printf("Terminates execution.\n\n");
			
			printf("[help]\n");
			printf("Prints a short help doc to the terminal.\n\n");
			
			printf("[<n>]\n");
			printf("<n> is a positive number.  The command will print out the sum of base n to\n");
			printf("power n with the starting value of n by 1 at each summand until the value n\n");
			printf("equals 1.\n");
			printf("*******************************************************************************\n\n");
		}
		//The user entered a number <n>
		else if(input[0] >= '0' && input[0] <= '9')
		{
			int n;
			int valid_format = 0;
			//The following loop uses three flags to make sure the entire input entry is valid
			//valid_format checks to see if '0' to '9', ',' was entered
			n = 0;
			for(i = 0; i < strlen(input) - 1; i++)
			{
				if(input[i] >= '0' && input[i] <= '9')
					valid_format = 1;
				else
				{
					valid_format = 0;
					printf("\nYou entered an invalid entry!\n");
					printf("Positive numbers are only allowed.\n");
					break;
				}
			}
			n = atoi(input);


			if(valid_format == 1)
			{
				int count = n;
				printf("\n");
				while(count > 1)
				{
					printf("%d^%d + ", count, count);
					count--;
				}
				printf("%d^%d = ", count, count);
				printf("%d\n", sum_of_powers(n));
				printf("\n");
			}
		}
		//The user entered an invalid command
		else
		{
			printf("You entered an invalid command!\n\n");
			printf("Enter \"help\" for a list of commands\n");
		}
	}
}
