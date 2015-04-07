// Rat-in-a-maze by queue BFS using clockwise search of NESW.
// Note:   Positions are given as 1..rows and 1..cols.
//         Walls are placed around the maze, i.e. additional rows and cols.
// Input:  Dimensions m (rows) and n (columns).
//         Start position as row and column.
//         Final position as row and column.
//         Each wall as row and column.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int row,col;
} pair;

int maze[81][81];
int rows,cols;
pair start,stop;

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
scanf("%d %d",&start.row,&start.col);
if (start.row<1 || start.row>rows || start.col<1 || start.col>cols)
{
  printf("Fatal at %d\n",__LINE__);
  exit(0);
}
scanf("%d %d",&stop.row,&stop.col);
if (stop.row<1 || stop.row>rows || stop.col<1 || stop.col>cols)
{
  printf("Fatal at %d\n",__LINE__);
  exit(0);
}
if (start.row==stop.row && start.col==stop.col)
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
  if (i==start.row && j==start.col || i==stop.row && j==stop.col)
  {
    printf("Fatal at %d\n",__LINE__);
    exit(0);
  }
  maze[i][j]=1;
}
}

int qHead,qTail,qSize,qSlotsInUse,qMaxSlotsInUse;
pair q[81*81];
pair pred[81][81];

void queueInit(int numElements)
{
qSize=numElements+1;
qHead=qTail=qSlotsInUse=qMaxSlotsInUse=0;
}

int queueEmpty()
{
return qTail==qHead;
}

void enqueue(pair x)
{
q[qTail++]=x;
if (qTail==qSize)
  qTail=0;
if (qTail==qHead)
{
  printf("Fatal at %d\n",__LINE__);
  exit(0);
}
qSlotsInUse++;
if (qSlotsInUse>qMaxSlotsInUse)
  qMaxSlotsInUse=qSlotsInUse;
}

pair dequeue()
{
pair temp;

if (queueEmpty())
{
  printf("Fatal at %d\n",__LINE__);
  exit(0);
}
temp=q[qHead++];
if (qHead==qSize)
  qHead=0;
qSlotsInUse--;
return temp;
}

int BFS()
{
int i,j;
pair work,workNew;

for (i=0;i<=rows+1;i++)
  for (j=0;j<=cols+1;j++)
    pred[i][j].row=pred[i][j].col=(-999);
maze[start.row][start.col]=2;
pred[start.row][start.col].row=pred[start.row][start.col].col=(-1);
// Bound on queue size???
queueInit(rows+cols);
enqueue(start);
while (!queueEmpty())
{
  work=dequeue();
  // North
  workNew=work;
  workNew.row--;
  if (maze[workNew.row][workNew.col]==0)
  {
    maze[workNew.row][workNew.col]=2;
    pred[workNew.row][workNew.col]=work;
    if (workNew.row==stop.row && workNew.col==stop.col)
      break;
    enqueue(workNew);
  }
  // East
  workNew=work;
  workNew.col++;
  if (maze[workNew.row][workNew.col]==0)
  {
    maze[workNew.row][workNew.col]=2;
    pred[workNew.row][workNew.col]=work;
    if (workNew.row==stop.row && workNew.col==stop.col)
      break;
    enqueue(workNew);
  }
  // South
  workNew=work;
  workNew.row++;
  if (maze[workNew.row][workNew.col]==0)
  {
    maze[workNew.row][workNew.col]=2;
    pred[workNew.row][workNew.col]=work;
    if (workNew.row==stop.row && workNew.col==stop.col)
      break;
    enqueue(workNew);
  }
  // West
  workNew=work;
  workNew.col--;
  if (maze[workNew.row][workNew.col]==0)
  {
    maze[workNew.row][workNew.col]=2;
    pred[workNew.row][workNew.col]=work;
    if (workNew.row==stop.row && workNew.col==stop.col)
      break;
    enqueue(workNew);
  }
}
if (pred[stop.row][stop.col].row==(-999))
  return 0;
// Record final path using predecessors
for (work=workNew;
     work.row!=(-1);
     work=pred[work.row][work.col])
  maze[work.row][work.col]=3;
return 1;
}

main()
{
readInput();
printf("Initial maze:\n");
printMaze();
if (BFS())
  printf("Success:\n");
else
  printf("Failure:\n");
printMaze();
printf("queue used max of %d slots\n",qMaxSlotsInUse);
}
