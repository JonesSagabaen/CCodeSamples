/**************************************************************************************************
Jones Sagabaen
C Code Samples
This file is a part of a series of simple programs written in the C programming language.
Each program performs a simple function that requires user input.

Primary_or_Perfect.c
***************************************************************************************************/
#include<stdio.h>
#include <stdlib.h>

/*
Helper function that calculates prime numbers with a given start and finish value.
*/
void prime(int start, int finish)
{
	printf("Prime numbers are:\n");
	
	int num, divisor, limit, is_prime;
	num = start;
	limit = finish;
	divisor = 2;
	is_prime = 1;
	while(num < limit)
	{
		while(divisor < num)
		{
			if(num % divisor++ == 0)
				is_prime = 0;
		}
		if(is_prime == 1)
			printf("%d\n", num);
		is_prime = 1;
		num++;
		divisor = 2;
	}
}

/*
Helper function that calculates perfect numbers with a given start and finish value.
*/
void perfect(int start, int finish)
{
	printf("Perfect numbers are:\n");
	
	int num, divisor, true, divisor_array[100], position, sum;
	num = start;
	true = 0;
	int i;
	while(num < finish)
	{
		for(i = 0; i < 100; i++)
			divisor_array[i] = 0;
		divisor = 1;
		position = 0;
		while(divisor < num)
		{
			if(num % divisor == 0)
				divisor_array[position++] = divisor;
			divisor++;
		}
		sum = 0;
		position = 0;
		while(divisor_array[position] != '\0')
			sum += divisor_array[position++];
				
		if(sum == num)
			printf("Perfect Number is %d\n", num);
		
		num++;
		}
}

/*
Class calculates prime and perfect numbers based on the user's input.
*/
int main()
{
	while(1)
	{
		printf("\nPlease enter a command.\nEnter HELP for a list of commands.\n");
		int i;
		char input[10];
		fgets(input, 10, stdin);

		if(input[0] == 'h' || input[0] == 'H')
		{
			printf("\nHELP: Prints the list of commands\nPRIME: Prints prime numbers\nPERFECT: Prints perfect numbers\nQUIT: Terminates this program\n\n");
		}
		else if((input[0] == 'p' && input[1] == 'r') || (input[0] == 'P' && input[1] == 'R'))
		{
			printf("\nEnter one of the following commands\nDEFAULT: Continuously print prime numbers\nRANGE: Enter a range of numbers\n");
			fgets(input, 10, stdin);
			
			int loop;
			loop = 0;
			while(loop == 0)
			{
				/* Prime number and default parameters are entered. */
				if(input[0] == 'd' || input[0] == 'D')
				{
					prime(3, 100000000);
					loop = 1;
				}
				/* Prime number and range parameters are entered. */
				else if(input[0] == 'r' || input[0] == 'R')
				{
					int true, start, finish;
					true = 0;
					while(true == 0)
					{
						printf("Enter a valid positive starting value:\n");
						for(i = 0; i < 10; i++)
							input[i] = 0;
						fgets(input, 10, stdin);
						start = atoi(input);
						if(start >= 3)
							true = 1;
						else if(start < 3 && start >= 0)
						{
							start = 3;
							true = 1;
						}
					}
					true = 0;
					while(true == 0)
					{
						printf("Enter a valid positive ending value:\n");
						for(i = 0; i < 10; i++)
							input[i] = 0;
						fgets(input, 10, stdin);
						finish = atoi(input);
						if(finish > start)
							true = 1;
					}
					prime(start, finish);
					loop = 1;
				}
				else
					printf("An invalid command was entered.\n");
			}
		}
		else if((input[0] == 'p' && input[1] == 'e') || (input[0] == 'P' && input[1] == 'E'))
		{
			printf("\nEnter one of the following commands\nDEFAULT: Continuously print prime numbers\nRANGE: Enter a range of numbers\n");
			fgets(input, 10, stdin);
			
			int loop;
			loop = 0;
			while(loop == 0)
			{
				/* Prime number and range parameters are entered. */
				if(input[0] == 'd' || input[0] == 'D')
				{
					perfect(3, 100000000);
					loop = 1;
				}
				/* Perfect number and range parameters are entered. */
				else if(input[0] == 'r' || input[0] == 'R')
				{
					int true, start, finish;
					true = 0;
					while(true == 0)
					{
						printf("Enter a valid positive starting value:\n");
						for(i = 0; i < 10; i++)
							input[i] = 0;
						fgets(input, 10, stdin);
						start = atoi(input);
						if(start >= 3)
							true = 1;
						else if(start < 3 && start >= 0)
						{
							start = 3;
							true = 1;
						}
					}
					true = 0;
					while(true == 0)
					{
						printf("Enter a valid positive ending value:\n");
						for(i = 0; i < 10; i++)
							input[i] = 0;
						fgets(input, 10, stdin);
						finish = atoi(input);
						if(finish > start)
							true = 1;
					}
					perfect(start, finish);
				}
			}
		}
		else if(input[0] == 'q' || input[0] == 'Q')
		{
			return 0;
		}
		else
			printf("You entered an invalid option.\n");
	}
}
