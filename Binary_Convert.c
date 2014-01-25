/**************************************************************************************************
Jones Sagabaen
C Code Samples
This file is a part of a series of simple programs written in the C programming language.
Each program performs a simple function that requires user input.

Binary_Convert.c
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*
Method uses division to convert a given value to its binary form and prints it out to the console.
*/
void print_binary(int decimal)
{	
	int i = 0;
	int bin_values[80];
	while(decimal != 0)
	{
		bin_values[i++] = decimal % 2;
		decimal = decimal / 2;
	}
	bin_values[i] = '\0';
	
	int j = i;
	while(j % 4 != 0)
	{
		printf("0");
		j++;
	}
	for(j = i - 1; j >= 0; j--)
	{
		printf("%d", bin_values[j]);
	}
}

/*
The purpose of the main method is to get the user's input and guide the user to print the various
forms of decimal values through a range of numbers.
*/
int main()
{
	while(1)
	{
		char input[10];
		int is_letters = 0;
		int k;
		//Following loop makes sure that the next user's input is between 'a' to 'z', 'A' to 'Z'
		while(is_letters == 0)
		{
			printf("Enter \"help\" for a list of commands\n");
			printf("Please enter a command: ");
			fgets(input, 10, stdin);
			for(k = 0; k < strlen(input) - 1; k++)
			{
				if(input[k] >= 'a' && input[k] <= 'z')
				{
					input[k] = input[k] - 'a' + 'A';
					is_letters = 1;
				}
				else if(input[k] >= 'A' && input[k] <= 'Z')
					is_letters = 1;
				else
				{
					is_letters = 0;
					printf("\nYou entered an invalid entry!\n");
					printf("You entered an invalid character.\n\n");
					break;
				}
			}
		}
		//This if statement means the user typed "quit"
		if(input[0] == 'Q' && input[1] == 'U' && input[2] == 'I' && input[3] == 'T')
		{
			return 0;
		}
		//This if statement means the user typed "help"
		else if(input[0] == 'H' && input[1] == 'E' && input[2] == 'L' && input[3] == 'P')
		{
			printf("\n*******************************************************************************\n");
			printf("[range]\n");
			printf("This command proceeds to accept a valid range of the following format:\n");
			printf("<n1>,<n2>\n");
			printf("Typing this command gives the utility a start and stop point for printing \n");
			printf("numbers. The utility will also accept the command ,<n2> in which case it\n");
			printf("will start at zero and print a table up to <n2> and the command <n1>, in\n");
			printf("which case it will start at <n1> and report up to the precision limit of\n");
			printf("the machine you are running on.\n\n");
			
			printf("[quit]\n");
			printf("Terminates execution.\n\n");
			
			printf("[help]\n");
			printf("Prints a short help doc to the terminal.\n");
			printf("*******************************************************************************\n\n");
		}
		//This if statement means the user typed "range"
		else if(input[0] == 'R' && input[1] == 'A' && input[2] == 'N' && input[3] == 'G' && input[4] == 'E')
		{
			int start, end;
			int valid_format = 0;
			int comma_flag = 0;
			int range_flag = 0;
			//The following loop uses three flags to make sure the entire input entry is valid
			//valid_format checks to see if '0' to '9', ',' was entered
			//comma_flag checks to see if a comma is correctly placed
			//range_flag checks to see if the numbers are positive and the start value is less than the end value
			while(valid_format == 0 || comma_flag == 0 || range_flag == 0)
			{
				start = 0;
				end = 0;
				printf("Enter a valid range: ");
				fgets(input, 10, stdin);				
				for(k = 0; k < strlen(input) - 1; k++)
				{
					if(input[k] == '0' || input[k] == '1' || input[k] == '2' || input[k] == '3' || input[k] == '4' || input[k] == '5' || input[k] == '6' || input[k] == '7' || input[k] == '8' || input[k] == '9' || input[k] == ',')
						valid_format = 1;
					else
					{
						valid_format = 0;
						printf("\nYou entered an invalid entry!\n");
						printf("The range of positive values must follow the form:\n");
						printf("	start,end\n");
						printf("Spaces are not allowed.\n");
						break;
					}
				}
			
				int i, j;
				int comma = -1;
				for (i = 0; i < 10; i++)
				{
					if (input[i] == ',')
					{
						comma = i;
						comma_flag = 1;
					}
				}
				if(comma == -1)
				{
					comma_flag = 0;
					printf("The comma was not correctly placed!\n");
				}
				
				char temp[10];
				for (i = 0; i < comma; i++)
				{
					temp[i] = input[i];
				}
				start = atoi(temp);
							
				if(comma + 2 == strlen(input))
					end = 1000;
				else
				{
					i = 0;
					for (j = comma + 1; j < strlen(input); j++)
					{
						temp[i] = input[j];
						i++;
					}
					
					end = atoi(temp);
				}				
				if(start > end)
				{
					range_flag = 0;
					printf("You entered an invalid entry!\n");
					printf("The start value is larger than the end value.\n");
				}
				else
					range_flag = 1;
				printf("\n");
			}
			
			//The following lines perform the core functionality where the various forms of decimal values are printed
			printf("dec		oct		hex		bin\n");
			int l;
			for(l = start; l <= end; l++)
			{
				printf("%d		%o		%x		", l, l, l);
				print_binary(l);
				printf("\n");
			}
			printf("\n");
		}
		else
			printf("\nAn invalid command was entered!\n\n");
	}
}
