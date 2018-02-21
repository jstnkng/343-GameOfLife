#include<stdio.h>
#include<stdlib.h>
#include"file_utilities.h"
#include<string.h>


void playGeneration();


int main(int argc, char **argv)
{
	char *gameFile;
	char ch;
	int boardWidth, boardHeight, generation;
	char *board;
	
	if (argc < 3){
		printf("Error: Play the game by running ./Life [boardWidth] [boardHeight]\n");
		printf("Example (./Life 5 4  will create a 5x4 grid for the board.\n");
		return(1);
	}
	else
	{
		int x,y;
		int size;
		boardHeight = atoi(argv[1]);
		boardWidth = atoi(argv[2]);
		setWidth(boardWidth);
		setHeight(boardHeight);

		if (boardHeight > boardWidth)
			size = boardHeight;
		else 
			size = boardWidth;
		char boardValues[boardWidth*boardHeight+1];
		
		initialize();
		int i;
		for (i=0; i< boardWidth*boardHeight+1; i++)
			boardValues[i] = getValue(i);
		board = boardValues;
		
		gameFile = "input.txt";
		
		write_file(gameFile, board, size);
		read_file(gameFile, &board);
		//write_file(gameFile, board, 0);
		char options[99] = "\nChoose an option: (s)ave, (l)oad, (c)ontinue, (i)terate, or (q)uit\n";
		printf(options);
		char option;
		scanf(" %c", &option);
		while(option != 'q')
		{
			if (option == 's')
			{
				printf("Enter a file name to save to: ");
				char newFile[99];
				scanf(" %s", newFile);
				write_file(newFile, board, size);
				printf("File saved successfully\n");
				printf(options);
				scanf(" %c", &option);
			}
			if (option == 'l')
			{
				printf("Enter a file name to load: ");
				char loadFile[99];
				scanf(" %s", loadFile);
				read_file(loadFile, &board);
				gameFile = loadFile;
				printf(options);
				scanf(" %c", &option);
			}
			if (option == 'c')
			{
				int gen = getGeneration();
				setGeneration(gen + 1);
				write_file(gameFile, board, 0);
				read_file(gameFile, &board);
				printf(options);
				scanf(" %c",&option);
			}
			if (option == 'i')
			{
				int iterations = 0;
				printf("Enter the number of times to iterate: ");
				scanf(" %d", &iterations);
				int gen = getGeneration();
				setGeneration(gen + iterations);
				write_file(gameFile, board, 0);
				read_file(gameFile, &board);
				printf(options);
				scanf(" %c", &option);
			}	
			else
			{
				printf("Invalid input...\nInput was %c", option);
				printf(options);
				scanf(" %c", &option);
			}
		}
	}

	return 0;
}

void playGeneration(int iterations, char *filename, char *board, char **grid, int size )
{
	int i,x,y;
	int neighbors;
	for (i=0; i<iterations;i++)
	{
		for (x=0; x < getWidth(); x++)
			for (y=0; y < getHeight(); y++)
			{
				if (grid[x][y] == '1')
				{
					if (x > 0)
					{
						if (grid[x-1][y] == '1'){
							neighbors++;
						}						
					}
					if (x < getWidth())
					{
						if (grid[x+1][y] == '1')
						{
							neighbors++;
						}
					}
					if (y > 0)
					{
						if (grid[x][y-1] == '1')
						{
							neighbors++;
						}
					}
					if ( y < getHeight())
					{
						if (grid[x][y+1] == '1')
						{
							neighbors++;
						}
					}
					if (neighbors < 2 || neighbors > 3)
					{
						grid[x][y] = '0';
						neighbors = 0;
					}
					
				}
				else if (grid[x][y] == '0')
				{

					if (x > 0)
                                        {
                                                if (grid[x-1][y] == '1'){
                                                        neighbors++;
                                                }
                                        }
                                        if (x < getWidth())
                                        {
                                                if (grid[x+1][y] == '1')
                                                {
                                                        neighbors++;
                                                }
                                        }
                                        if (y > 0)
                                        {
                                                if (grid[x][y-1] == '1')
                                                {
                                                        neighbors++;
                                                }
                                        }
                                        if ( y < getHeight())
                                        {
                                                if (grid[x][y+1] == '1')
                                                {
                                                        neighbors++;
                                                }
                                        }
                                        if (neighbors == 3)
                                        {
					       grid[x][y] = '1';
						neighbors = 0;
					}
                                  }
			}

	}
}


