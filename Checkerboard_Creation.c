/**************************************************************************************************
Jones Sagabaen
C Code Samples
This file is a part of a series of simple programs written in the C programming language.
Each program performs a simple function that requires user input.

Checkerboard_Creation.c
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define DOMINO_SIZE 2

int static rows;
int static columns;
int static grid_occupier[51][51];

/*
Method prints the checkerboard based on the rows and columns the user has entered.
It also uses the multidimensional array to see which boxes in the checkerboard is indicated as marked.
*/
void print_board()
{
	int i, j, l;
	int k = 0;
	printf("  ");
	for(l = 1; l <= columns; l++)
		printf("   %d  ", l);
	l = 1;
	for(i = 0; i < rows * 4; i++)
	{
		if(i % 4 == 0)
			printf("\n  +");
		else
		{
			if(i % 4 == 2)
				if(l >= 10)
					printf("\n%d|", l++);
				else
					printf("\n%d |", l++);
			else
				printf("\n  |");
		}
		if(i % 4 == 0)
			for(j = 0; j < columns; j++)
				printf("-----+");
		else
			for(j = 0; j < columns; j++)
			{
				if(grid_occupier[i/4][j] == -1)
				{
					if(i % 4 == 1)
					{
						printf("\\\\ //|");
						k++;
					}
					else if(i % 4 == 2)
					{
						printf(" XXX |");
						k++;
					}
					else if(i % 4 == 3)
					{
						printf("// \\\\|");
						k = 0;
					}
				}
				else if(grid_occupier[i/4][j] > 0)
				{
					if(i % 4 == 1)
					{
						printf("     |");
						k++;
					}
					else if(i % 4 == 2)
					{
						if(grid_occupier[i/4][j] >= 10 && grid_occupier[i/4][j] <= 100)
							printf("  %d |", grid_occupier[i/4][j]);
						else if(grid_occupier[i/4][j] >= 100 && grid_occupier[i/4][j] <= 1000)
							printf(" %d |", grid_occupier[i/4][j]);
						else
						{
							printf("  %d  |", grid_occupier[i/4][j]);
							k++;
						}
					}
					else if(i % 4 == 3)
					{
						printf("     |");
						k = 0;
					}
				}
				else
					printf("     |");
			}
	}
	printf("\n  +");
	for(j = 0; j < columns; j++)
	{
		printf("-----+");
	}
	printf("\n");
}

/*
Method uses the domino tiles and goes through the current checkboard to fill up the maximum size of the board.
*/
void solve(int recursion, int tile_number)
{
	int i, j;
	for(i = 0; i < 51 && i < rows; i++)
		for(j = 0; j < 51 && j < columns; j++)
		{
			if(grid_occupier[i][j] == 0 && grid_occupier[i][j + 1] == 0 && j + 1 < columns)
			{
				grid_occupier[i][j] = tile_number;
				grid_occupier[i][j + 1] = tile_number;
				return solve(recursion + 1, tile_number + 1);
			}
			else if(grid_occupier[i][j] == 0 && grid_occupier[i + 1][j] == 0 && i + 1 < rows)
			{
				grid_occupier[i][j] = tile_number;
				grid_occupier[i + 1][j] = tile_number;
				return solve(recursion + 1, tile_number + 1);
			}
		}
}

/*
Method gets the various user commands and extracts the information to alter the state of the checkboard
and its marked boxes.
*/
int get_input()
{
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
					else if(input[i] >= 'A' && input[i] <= 'Z' || input[i] >= '0' && input[i] <= '9' || input[i] == ',')
						valid_character = 1;
					else
					{
						valid_character = 0;
						printf("\nYou entered an invalid entry!\n");
						printf("You entered an invalid character.\n\n");
						break;
					}
				}
			}
			//The user entered "quit"
			if(input[0] == 'Q' && input[1] == 'U' && input[2] == 'I' && input[3] == 'T')
				return 0;
			//The user entered "help"
			else if(input[0] == 'H' && input[1] == 'E' && input[2] == 'L' && input[3] == 'P')
			{
				printf("\n*******************************************************************************\n");
				printf("[quit]\n");
				printf("Terminates execution.\n\n");
				
				printf("[help]\n");
				printf("Prints a short help doc to the terminal.\n\n");
				
				printf("[print]\n");
				printf("Prints the current layout of the checkerboard.\n\n");
				
				printf("[rows <n1>]\n");
				printf("<n1> is a positive integer to indicate how many rows that the checkerboard\n");
				printf("is to print out.\n\n");
				
				printf("[columns <n2>]\n");
				printf("<n2> is a positive integer to indicate how many columns that the checkerboard\n");
				printf("is to print out.\n\n");
				
				printf("[<n1>,<n2>]\n");
				printf("<n1>,<n2> refer to the <row>,<column> address of a single square on the \n");
				printf("checkerboard.  An \"X\" will be set or removed within the indicated position.\n\n");
				
				printf("[solve]\n");
				printf("Given the dimensions of the checkerboard and the X'ed out boxes on the\n");
				printf("checkerboard grid, dominos will be placed within the board to see whether the\n");
				printf("board can completely filled.  If even one box on the checkboard grid is\n");
				printf("available, the function will return indicating that the board is unsolvable.\n");
				
				printf("-------------------------------------------------------------------------------\n");
				printf("Note: Checkboard may not properly print when given large values for the rows\n");
				printf("      and columns due to the varied sizes of the user's terminal.\n");
				printf("-------------------------------------------------------------------------------\n");
				printf("*******************************************************************************\n\n");
			}
			//The user entered "print"
			else if(input[0] == 'P' && input[1] == 'R' && input[2] == 'I' && input[3] == 'N' && input[4] == 'T')
			{
				print_board();
			}
			//The user entered "rows <n1>"
			else if(input[0] == 'R' && input[1] == 'O' && input[2] == 'W' && input[3] == 'S')
			{
				int valid_format = 1;
				for (i = 4; i < strlen(input) - 1; i++)
				{					
					if(i == 4)
					{
						if(input[4] >= '0' && input[4] <= '9')
						{
							printf("An invalid space was found before <n1>\n\n");
							valid_format = 0;
							break;
						}
					}
					else if(input[i] < '0' || input[i] > '9')
					{
						printf("An invalid character was found for <n1>\n\n");
						valid_format = 0;
						break;
					}
				}

				if(valid_format == 1)
				{
					char temp[strlen(input) - 5];
					int j = 0;
					for (i = 5; i < strlen(input); i++)
						temp[j++] = input[i];
					rows = atoi(temp);
					
					return 1;
				}
			}
			//The user entered "columns <n2>"
			else if(input[0] == 'C' && input[1] == 'O' && input[2] == 'L' && input[3] == 'U' && input[4] == 'M' && input[5] == 'N' && input[6] == 'S')
			{
				int valid_format = 1;
				for (i = 7; i < strlen(input) - 1; i++)
				{					
					if(i == 7)
					{
						if(input[7] >= '0' && input[7] <= '9')
						{
							printf("An invalid space was found before <n2>\n\n");
							valid_format = 0;
							break;
						}
					}
					else if(input[i] < '0' || input[i] > '9')
					{
						printf("An invalid character was found for <n2>\n\n");
						valid_format = 0;
						break;
					}
				}

				if(valid_format == 1)
				{
					char temp[strlen(input) - 8];
					int j = 0;
					for (i = 8; i < strlen(input); i++)
						temp[j++] = input[i];
					columns = atoi(temp);
					
					return 2;
				}
			}
			//The user entered "solve"
			else if(input[0] == 'S' && input[1] == 'O' && input[2] == 'L' && input[3] == 'V' && input[4] == 'E')
			{
				int recursion = 0;
				int tile_number = 1;
				solve(recursion, tile_number);
				if(recursion == 0)
				{				
					print_board();

					int i, j;
					int no_solution_flag = 0;
					for(i = 0; i < 51 && i < rows; i++)
						for(j = 0; j < 51 && j < columns; j++)
							if(grid_occupier[i][j] == 0)
								no_solution_flag = 1;
					if(no_solution_flag == 1)
						printf("This position has no solution.\n");
						
					for(i = 0; i < 51; i++)
						for(j = 0; j < 51; j++)
							grid_occupier[i][j] = 0;
				}
				else
					print_board();
			}
			//The user entered "<n1>,<n2>"
			else if(input[0] >= '0' && input[0] <= '9')
			{
				int n1, n2;
				int valid_format = 0;
				int comma_flag = 0;
				int range_flag = 0;
				//The following loop uses three flags to make sure the entire input entry is valid
				//valid_format checks to see if '0' to '9', ',' was entered
				//comma_flag checks to see if a comma is correctly placed
				//range_flag checks to see if the n1 and n2 values don't exceed the size of the board
				n1 = 0;
				n2 = 0;
				for(i = 0; i < strlen(input) - 1; i++)
				{
					if(input[i] == '0' || input[i] == '1' || input[i] == '2' || input[i] == '3' || input[i] == '4' || input[i] == '5' || input[i] == '6' || input[i] == '7' || input[i] == '8' || input[i] == '9' || input[i] == ',')
						valid_format = 1;
					else
					{
						valid_format = 0;
						printf("\nYou entered an invalid entry!\n");
						printf("The range of positive values must follow the form:\n");
						printf("	n1,n2\n");
						printf("Spaces incorrectly placed.\n");
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
				n1 = atoi(temp);
							
				if(comma + 2 == strlen(input))
					n2 = 1000;
				else
				{
					i = 0;
					for (j = comma + 1; j < strlen(input); j++)
					{
						temp[i] = input[j];
						i++;
					}
					
					n2 = atoi(temp);
				}

				n1--;
				n2--;
				if(n1 > rows - 1)
				{
					range_flag = 0;
					printf("Square is off board - input ignoreed.\n");
					printf("The n1 value is larger than the board's row size.\n");
				}
				else if(n2 > columns - 1)
				{
					range_flag = 0;
					printf("Square is off board - input ignoreed.\n");
					printf("The n2 value is larger than the board's column size.\n");
				}
				else
					range_flag = 1;
				printf("\n");
				
				if(!(valid_format == 0 || comma_flag == 0 || range_flag == 0))
				{
					if(grid_occupier[n1][n2] == 0)
						grid_occupier[n1][n2] = -1;
					else
						grid_occupier[n1][n2] = 0;
					return 3;
				}
			}
			else
			{
				printf("Command not understood.\n\n");	
				printf("Enter \"help\" for a list of commands\n");
			}
	}
}

/*
The main method uses the print_board() and the get_input() to get the user's input and print
the checkerboard based on the user's commands.
*/
int main()
{
	rows = 8;
	columns = 8;
	int i, j;
	for(i = 0; i < 51; i++)
		for(j = 0; j < 51; j++)
			grid_occupier[i][j] = 0;
	
	printf("Welcome to the checkerboard tiling program!\n");
	printf("(Domino size is 1 x %d)\n", DOMINO_SIZE);
	print_board();	
	while(get_input() != 0)
		print_board();
	printf("\n*******************************************************************************\n");
	printf("Okay, come on back when you can stay longer!\n");
	printf("*******************************************************************************\n");
	return 0;
}
