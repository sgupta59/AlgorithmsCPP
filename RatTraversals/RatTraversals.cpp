// Rat-in-a-maze by stack DFS using clockwise search of NESW.
// Note:   Positions are given as 1..rows and 1..cols.
//         Walls are placed around the maze, i.e. additional rows and cols.
// Input:  Dimensions m (rows) and n (columns).
//         Start position as row and column.
//         Final position as row and column.
//         Each wall as row and column.
// http://ranger.uta.edu/~weems/NOTES2320/VERMIN/
//http://www.sharjah.ac.ae/en/about/agc/conferences/ME-GPC/Documents/Chapter%208%20-%20Backtracking.pdf
//http://www.cse.msu.edu/~torng/Classes/Archives/cse830.02spring/
//file:///C:/Users/kg/Desktop/interviews/backtracking/torng_cs3830.pdf
//file:///C:/Users/kg/Desktop/interviews/fundamentals-of-algorithmics-brassard_ingles.pdf



#include <stdio.h>
#include < stdlib.h >
#include <cstdlib>
#include "stdafx.h"
int maze[81][81];
int rows,cols;
int startRow,startCol,stopRow,stopCol;
using namespace std;
void printMaze()
{
	int i,j;

	for (i=0;i<=rows+1;i++)
	{
		for (j=0;j<=cols+1;j++)
		{
			switch (maze[i][j]) {
			case 0:
				printf(" "); // Open space, never discovered
				break;
			case 1:
				printf("."); // Wall
				break;
			case 2:
				printf("^"); // Dead end path
				break;
			case 3:
				printf("#"); // Path between start and stop
				break;
			default:
				printf("\nFatal at %d\n",__LINE__);
				//exit(0);
			}
			printf(" ");
		}
		printf("\n");
		
	}
	printf("\n");
}

void readInput()
{
	int i,j;
	FILE* pFile;
	pFile = fopen("a.dat", "r+");
	fscanf(pFile,"%d %d",&rows,&cols);
	// Walls for rows 0 and rows+1
	for (j=0;j<=cols+1;j++)
		maze[0][j]=maze[rows+1][j]=1;
	// Walls for columns 0 and cols+1
	for (i=1;i<=rows;i++)
		maze[i][0]=maze[i][cols+1]=1;
	// Clear out interior of maze
	for (i=1;i<=rows;i++)
		for (j=1;j<=cols;j++)
			maze[i][j]=0;
	fscanf(pFile,"%d %d",&startRow,&startCol);
	if (startRow<1 || startRow>rows || startCol<1 || startCol>cols)
	{
		printf("Fatal at %d\n",__LINE__);
		//exit(0);
	}
	fscanf(pFile,"%d %d",&stopRow,&stopCol);
	if (stopRow<1 || stopRow>rows || stopCol<1 || stopCol>cols)
	{
		printf("Fatal at %d\n",__LINE__);
		//exit(0);
	}
	if (startRow==stopRow && startCol==stopCol)
	{
		printf("Fatal at %d\n",__LINE__);
		//exit(0);
	}
	while (fscanf(pFile,"%d %d",&i,&j)!=EOF)
	{
		if (i<1 || i>rows || j<1 || j>cols)
		{
			printf("Fatal at %d\n",__LINE__);
			//exit(0);
		}
		if (i==startRow && j==startCol || i==stopRow && j==stopCol)
		{
			printf("Fatal at %d\n",__LINE__);
			//exit(0);
		}
		maze[i][j]=1;
	}
}

typedef enum {init,north,east,south,west} direction;
typedef struct {
	int row,col;
	direction current;
} stackEntry;
stackEntry stack[81*81];  // Bound on stack size?
int sp=(-1);  // stack is empty

int emptyStack()
{
	return sp==(-1);
}

void pushStack(stackEntry x)
{
	stack[++sp]=x;
}

stackEntry popStack()
{
	return stack[sp--];
}

int canMove(int row, int col)
{
	if (maze[row][col] == 1)
		return 0;
	return 1;
}
void getRowCol(int row, int col, int dir, int& rowOut, int& colOut)
{
	if (dir == 1)
		colOut = colOut-1;
	else if (dir == 2)
		colOut = colOut+1;
	else if (dir == 3)
		rowOut = rowOut-1;
	else
		rowOut = rowOut+1;
}

int isASolution(int row, int col)
{
    if (row == stopRow && col == stopCol)
	{
		maze[row][col] = 3;
		return 1;
	}
    return 0;
}

int DFS_recursive(int row, int col)
{
    

    /** If this is a solution, then return */
	if (isASolution(row,col) == 1)
        return 1;

    /**
     * The cell will never be visited if it is marked. Typical DFS search.
    */
	maze[row][col] = 2;
    /**
    * For all children of this cell, visite them
    */
	for (int idx = 1; idx <=4; ++idx)
	{
		int rowOut = row;
		int colOut = col;
		getRowCol(row, col, idx,rowOut,colOut);
        /**
         * If this is a child (in this case not a wall) and is not visited
         * then visit it.
         */
		if (canMove(rowOut,colOut) && maze[rowOut][colOut] == 0)
		{
			printMaze();
            /** 
            * If there is a solution, then mark the cell and return
            */
			if (DFS_recursive(rowOut,colOut) == 1)
			{
				maze[rowOut][colOut] = 3;
				return 1;
			}
		}
	}
    /** 
     * Unmark the cell and return failure.
     * The unmarking occurs in backtracking so as to reuse the same cell in a different solution.
     */
	maze[row][col] = 0;
	printMaze();
    // Return failure.
	return 0;
}

int DFS_stack(int row,int col)
{
	stackEntry work;
	int returnValue;

	work.row=row;
	work.col=col;
	work.current=init;
	pushStack(work);
	while (!emptyStack())
	{
		work=popStack();
		if (work.current==init)  // Just arrived here?
		{
			if (maze[work.row][work.col]!=0)  // Not an open slot?
			{
				returnValue=0;
				continue;
			}
			if (work.row==stopRow && work.col==stopCol)  // At destination?
			{
				maze[work.row][work.col]=3;
				returnValue=1;
				continue;
			}
			maze[work.row][work.col]=2;  // Mark slot as discovered
			printMaze();
		}
		else if (returnValue==1)  // Backtracking from successful search?
		{
			maze[work.row][work.col]=3;
			continue;
		}
		else if (work.current==west)  // No other directions to try
		{
			returnValue=0;
			continue;
		}
		// Try next direction.  Push current position and new position
		work.current =  (direction)(work.current+1);
		pushStack(work);
		switch (work.current) {
		case north:
			work.row--;
			break;
		case east:
			work.col++;
			break;
		case south:
			work.row++;
			break;
		case west:
			work.col--;
			break;
		}
		work.current=init;
		pushStack(work);
	}

	return returnValue;
}

void main()
{
	readInput();
	printf("Initial maze:\n");
	printMaze();
	if (DFS_recursive(startRow,startCol))
		printf("Success:\n");
	else
		printf("Failure:\n");
	printMaze();
}