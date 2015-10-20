#include <iostream>
#include <string>

using namespace std;
// is it safe to put a queen at position (col, row) based on the current queenList
bool IsSafe(int queenList[], int col, int row)
{
    for (int tempCol = 1; tempCol < col; tempCol++)
    {
		// no need to check tempCol == col as we know they won't be same
        if ( queenList[tempCol] == row ||   // same row
			 col-tempCol == abs(queenList[tempCol] - row)) // diagonal 
		{
			return false;
		}
    }

    return true;
}
void PrintSolution(int N, int queenList[])
{
    for (int i=1; i<=N; i++)
    {
        cout<<queenList[i]<<" ";
    }

	cout << endl;
}
// found solution
void PlaceQueen(int N, int col, int* queenList, int &sum)
{
	if (col > N) // found the solution
    {
        sum++;
		PrintSolution( N, queenList );
		return;
    }

    for( int row=1; row<=N; row++ )
    {
    	if(IsSafe(queenList, col, row))
        {
	        queenList[col] = row;
            PlaceQueen(N, col+1, queenList, sum); // look for next col
            // no need to reset queenList[col] as the next iteration in the loop 
			// still use the same col, and IsSafe() only check the column less than
			// col, thus all the following columns settings are overwritten
        }
    }
	return;
}

bool isValidCandidate(int N, int* M, int row, int column)
{
	for (int col = 0; col < column; ++col)
	{
		if (row == M[col]) return false;
		if (abs(row-M[col]) == abs(col-column)) return false;
	}
	return true;
}
void EightQueen_SpaceEfficient(int N, int* M, int column, int& size)
{
	// if this is the solution node, print and return.
	// solution is if column == N
	if (column == N)
	{
		++size;
		return;
	}
	// for given column, start placing the queen at each row and solve.
	for (int row = 0; row < N; ++row)
	{
		// if [row,column] is a valid solution
		// call Eightqueen again.
		if (isValidCandidate(N, M, row, column))
		{
			M[column] = row;
			EightQueen_SpaceEfficient(N, M, column+1, size);
		}
	}
}
/**
 * Check only up to row -1 as the queen is placed on the row and we move row by row downward.
 */
bool isSafe(int** M, int length, int row, int col)
{
	for (int i = 0; i < row; ++i)
		if (M[i][col] == 1) return false;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < length; ++j)
		{
			if (M[i][j] != 0)
			{
				if (abs(i-row) == abs(j-col))
					return false;
			}
		}
	}
	return true;
}
bool eightQueen(int** M, int length, int row, int& count)
{
	// check for success. 
	if (row == length)
	{
		++count;
		return true;
	}
	// mark positioning queen at (x,y)
	 

	// get moves from this position, i.e place the queen on the next row
	for (int col = 0; col < length; ++col)
	{
		if (isSafe(M, length, row, col))
		{
			M[row][col] = 1;
			eightQueen(M, length, row+1, count);
			M[row][col] = 0;
		}
	}
	return false;
}
void main()
{
	int size = 8;

	int* queenList = new int[size+1];
	int sum = 0;
	int* sol = new int[size];
	EightQueen_SpaceEfficient(size,sol,0,sum);
    PlaceQueen(size, 1, queenList, sum);


	int** M = new int*[size];
	for (int i = 0; i < size; ++i)
		M[i] = new int[size];
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			M[i][j] = 0;
	int count = 0;
	eightQueen(M, size, 0,count);

	for (int i = 0; i < size; ++i)
		delete [] M[i];
	delete [] M;
}