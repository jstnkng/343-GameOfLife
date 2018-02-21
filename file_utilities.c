#include"file_utilities.h"
#include<stdio.h>
#include<stdlib.h>

static int generation, boardWidth, boardHeight;

static int x,y;

static int max;

static char** grid;

int getGeneration()
{
	return generation;
}

void setGeneration(int value)
{
	generation = value;
}

int getWidth()
{
	return boardWidth;
}

void setWidth(int value)
{
	boardWidth = value;
}

int getHeight()
{
	return boardHeight;
}

void setHeight(int value)
{
	boardHeight = value;
}

char values[1];

char getValue(int x)
{
	return values[x];
}

int read_file(char* filename, char **buffer){

	FILE *fin;
	fin = fopen(filename, "r");
	int generation, boardWidth, boardHeight;
	fscanf(fin, "%d %d %d",&generation, &boardWidth, &boardHeight); 
	buffer = (char **)malloc(boardWidth * sizeof(char *));
	

	//int values[boardWidth*boardHeight + 1];
	for (x=0; x < boardWidth*boardHeight+1; x++)
		fscanf(fin, "%c", &values[x]);

	for (x=0; x < boardWidth; x++)
		buffer[x] = (char *)malloc(boardWidth * sizeof(char));

	for (x=0; x <  boardWidth; x++)
		for (y=0; y < boardHeight; y++)
		{
			buffer[x][y] = values[max*x+y+1];
		}
	
	if (fin == NULL)
	{
		printf("Unable to read file...");
		return 0;
	}
	else
	{
		fclose(fin);
		printf("Generation: %d\n", generation);
		
		for (x=0; x < boardWidth; x++)
		{
			for(y=0; y < boardHeight; y++)
			{
				printf("%c", buffer[x][y]);
				if (y+1 ==  boardHeight)
					printf("\n");
							
			}
		}
		return 1;
	}
	free(buffer);
}

int write_file(char* filename, char *buffer, int size){
	FILE *file;
	values[1] = '0';
	file = fopen(filename, "w");
	fprintf(file, "%d %d %d\n", generation, boardWidth, boardHeight);
	for(x=0; x < boardWidth; x++)
		for (y=0; y < boardHeight; y++)
			fprintf(file, "%c", buffer[max*x+y+1]);
	fclose(file);
}

void initialize()
{
	for(x=0; x < boardWidth*boardHeight+1; x++)
		values[x] = '0';
	
	values[boardWidth/2+boardHeight] = '1';
	values[boardWidth/2-1+boardHeight+1] = '1';	
	//values[(boardWidth/2+1)+boardHeight+1] = '1';
	//values[8] = '1';
	if (boardWidth > boardHeight)
		max = boardWidth;
	else 
		max = boardHeight;
}
