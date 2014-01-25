/**************************************************************************************************
Jones Sagabaen
C Code Samples
This file is a part of a series of simple programs written in the C programming language.
Each program performs a simple function that requires user input.

Sum_of_Divisors.c
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "i2da.c"

#define STATUS_COL 0
#define STEPS_COL 1

int DEBUG_DIVSUM = 0;

int DEBUG_PRINT_STATEMENTS = 0;

struct infinite_array data_array;

/*
Method calculates the sum of divisors based on a given number.
*/
int divsum(int num)
{
	int divisor, position, divisor_array[100], sum;
	
	int i;
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
	{
		if(DEBUG_DIVSUM == 1)
		{
			if(divisor_array[position + 1] == '\0')
				printf("%d", divisor_array[position]);
			else
				printf("%d + ", divisor_array[position]);
		}
		
		sum += divisor_array[position++];
	}

	return sum;
}

/*
Method enables a debug mode to test the divsum() method.
*/
void divsum_test()
{
	DEBUG_DIVSUM = 1;
	while(1)
	{
		int num = 0;
		char input[10];
		printf("Type \"quit\" to exit.\n");
		printf("Enter a number: ");
		fgets(input, 20, stdin);
		if(input[0] == 'q' || input[0] == 'Q')
		{
			printf("Test conluded.\n");
			break;
		}
		num = atoi(input);

		printf("divsum() test\n");
		printf("divsum(%d) = ", num);
		printf(" = %d\n", divsum(num));
		printf("\n");
	}
	DEBUG_DIVSUM = 0;
	exit(8);
}

/*
Method enables a debug mode where helpful print statements are used to give useful information about the program.
*/
void enable_debug()
{
	DEBUG_PRINT_STATEMENTS = 1;
}

/*
Method is called when a loop through elements in the array are found.
As of this implementation, it merely locates amicable pairs, harmonious quadruplet and congenial triplet.
*/
void loop_found(int starting_num, int ending_num)
{
	int first, second, third, fourth;
	first = starting_num;
	second = divsum(first);
	third = divsum(second);
	fourth = divsum(third);
	if(first == divsum(second))
		printf("%d and %d form a amicable pair.\n", first, second); 
	else if(first == divsum(third))
		printf("%d, %d and %d form a harmonious quadruplet.\n", first, second, third); 
	else if(first == divsum(fourth))
		printf("%d, %d, %d and %d form a congenial triplet.\n", first, second, third, fourth);
}

int main(void)
{
//Debug statements: Remove line comments to enable debug methods.
//	divsum_test();
//	enable_debug();
	
	static int current_num = 0;
	static int iteration = 1;
	
	printf("Welcome to the sigma loop finder program!\n\n");
	printf("Enter \"help\" for a list of commands\n");
	while(1)
	{
		char input[10];
		int valid_character = 0;
		int i;
		while(valid_character == 0)
		{
			printf("Enter a command: ");
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
					printf("\nCommand not understood!\n");
					printf("An invalid character was entered.\n\n");
					printf("Enter \"help\" for a list of commands\n");
					break;
				}
			}
		}
		//The user entered "quit"
		if(input[0] == 'Q' && input[1] == 'U' && input[2] == 'I' && input[3] == 'T')
		{
			printf("\n*******************************************************************************\n");
			printf("Have a nice day!\n");
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
			printf("The input value <n> is the number of elements the program will proceed to\n");
			printf("calculate starting from the value 1.  At each element, the program will\n");
			printf("calculate whether there is a loop through reoccuring elements which is\n");
			printf("determined by calculating the sum of the element's divisors.\n");
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
					printf("\nCommand not understood!\n");
					printf("Positive numbers are only allowed.\n");
					break;
				}
			}
			n = atoi(input);

			if(n < iteration)
			{
				valid_format = 0;
				printf("<n> is less than the next iteration set of elements to calculate!\n\n");
			}

			if(valid_format == 1)
			{
				int steps, divsum_result;
				ia_init(&data_array);
				while(iteration <= n)
				{
					steps = 1;
					current_num = iteration;
					
					//Use current_num and set its status to -1 (number in progress)
					ia_store(&data_array, current_num, STATUS_COL, -1);
					divsum_result = divsum(current_num);
					if(divsum_result == 1)
					{
						ia_store(&data_array, current_num, STEPS_COL, 0);	//Set data[current_num][steps] = 0 (prime)
						//printf("%d is a prime number.\n", current_num);
					}
					else if(divsum_result == current_num)
					{
						ia_store(&data_array, current_num, STEPS_COL, 1);	//Set data[current_num][steps] = 1 (perfect)
						printf("%d is a perfect number.\n", current_num);
					}
					else
					{
						if(DEBUG_PRINT_STATEMENTS == 1)
							printf("iteration = %d\n   current_num = %d\n", iteration, current_num);
						ia_store(&data_array, current_num, STEPS_COL, steps++);	//Set data[current_num][steps] = number_of_steps
						ia_store(&data_array, current_num, STATUS_COL, -1);		//Set data[current_num][status] = -1 (in_progress)
						current_num = divsum_result;
						if(DEBUG_PRINT_STATEMENTS == 1)
							printf("   immediately after divsum(current_num) = %d\n", current_num);
						while(steps < 10)
						{
							if(ia_get(&data_array, current_num, STEPS_COL) > 0)
							{
								loop_found(iteration, current_num);
								break;
							}
							ia_store(&data_array, current_num, STEPS_COL, steps++);	//Set data[current_num][steps] = number_of_steps
							ia_store(&data_array, current_num, STATUS_COL, -1);		//Set data[current_num][status] = -1 (in_progress)
							current_num = divsum(current_num);
							if(DEBUG_PRINT_STATEMENTS == 1)
								printf("   next current_num = %d\n", current_num);
						}
					}
						
					if(current_num == iteration)
						ia_store(&data_array, current_num, STATUS_COL, 1);		//Set data[current_num][status] = 1 (done)
					else
					{
						current_num = iteration;
						int j;
						for(j = 0; j < steps; j++)
						{
							ia_store(&data_array, current_num, STATUS_COL, -1);	//Set data[current_num][status] = 1 (done)
							current_num = divsum(current_num);
						}
					}
						
						
					steps = 1;
					iteration++;
				}
			}
		}
		//The user entered an invalid command
		else
		{
			printf("Command not understood!\n\n");
			printf("Enter \"help\" for a list of commands\n");
		}
	}
}
