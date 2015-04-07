// Rat-in-a-maze by recursive DFS using clockwise search of NESW.
// Note:   Positions are given as 1..rows and 1..cols.
//         Walls are placed around the maze, i.e. additional rows and cols.
// Input:  Dimensions m (rows) and n (columns).
//         Start position as row and column.
//         Final position as row and column.
//         Each wall as row and column.

#include <stdio.h>
#include <stdlib.h>

int maze[81][81];
int rows,cols;
int startRow,startCol,stopRow,stopCol;

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
        exit(0);
    }
    printf(" ");
  }
  printf("\n");
}
}

void readInput()
{
int i,j;

scanf("%d %d",&rows,&cols);
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
scanf("%d %d",&startRow,&startCol);
if (startRow<1 || startRow>rows || startCol<1 || startCol>cols)
{
  printf("Fatal at %d\n",__LINE__);
  exit(0);
}
scanf("%d %d",&stopRow,&stopCol);
if (stopRow<1 || stopRow>rows || stopCol<1 || stopCol>cols)
{
  printf("Fatal at %d\n",__LINE__);
  exit(0);
}
if (startRow==stopRow && startCol==stopCol)
{
  printf("Fatal at %d\n",__LINE__);
  exit(0);
}
while (scanf("%d %d",&i,&j)!=EOF)
{
  if (i<1 || i>rows || j<1 || j>cols)
  {
    printf("Fatal at %d\n",__LINE__);
    exit(0);
  }
  if (i==startRow && j==startCol || i==stopRow && j==stopCol)
  {
    printf("Fatal at %d\n",__LINE__);
    exit(0);
  }
  maze[i][j]=1;
}
}

int DFS(int row,int col)
{
if (maze[row][col]!=0)
  return 0; // report failure
if (row==stopRow && col==stopCol)
{
  maze[row][col]=3;
  return 1; // report success
}
maze[row][col]=2;  // Mark slot as discovered
if (!DFS(row-1,col))       // Try North
  if (!DFS(row,col+1))     // Try East
    if (!DFS(row+1,col))   // Try South
      if (!DFS(row,col-1)) // Try West
        return 0;
maze[row][col]=3;  // On final path
return 1;  // Propagate success through recursion
}

main()
{
readInput();
printf("Initial maze:\n");
printMaze();
if (DFS(startRow,startCol))
  printf("Success:\n");
else
  printf("Failure:\n");
printMaze();
}
