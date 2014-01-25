/**************************************************************************************************
Jones Sagabaen
C Code Samples
This file is a part of a series of simple programs written in the C programming language.
Each program performs a simple function that requires user input.

Repeating_Sequence.c
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "ia.c"

/*
Main purpose of the program is investigate if a sequence of numbers eventually repeat 
calculated values
*/
int main(void)
{
	static int current_num = 0;
	static int iteration = 1;
	
	printf("Welcome to the sequence explorer program!\n\n");
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
			printf("The input value <n> is the number of iterations the program will proceed to\n");
			printf("calculate.  The starting value coincide with each iteration of calculation.\n");
			printf("And within each iteration, the starting value will proceed to calculate as\n");
			printf("n/2 if even, and 3n+1 if odd.  The iteration will end when a calculated number\n");
			printf("is revisited.\n");
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
				printf("<n> is less than the next iteration of sequence numbers to calculate!\n\n");
			}

			if(valid_format == 1)
			{	
				int steps;
				while(iteration <= n)
				{
					struct infinite_array data_array;	
					ia_init(&data_array);

					steps = 0;
					current_num = iteration;
					while(1)
					{
						//For debug purposes
//						printf("iteration = %d\n", iteration);
//						printf("current_num = %d\n", current_num);
//						printf("steps = %d\n", steps);
						
						if(current_num == 1)
						{
							printf("%d terminates at 1 after %d steps.\n", iteration, steps);
//							printf("\n");
							break;
						}
						if(ia_get(&data_array, current_num) == 1)	//Check data_array[current_num] if already visited
						{
							printf("%d terminates at %d after %d steps.\n", iteration, current_num, steps);
//							printf("\n");
							break;
						}

						ia_store(&data_array, 1, current_num);		//Mark n(current_num, 0) visited
						
						if(current_num % 2 == 0)	//even
						{
							current_num = current_num / 2;
						}
						else						//odd
						{
							current_num = 3 * current_num + 1;
						}
						steps++;
					}
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
