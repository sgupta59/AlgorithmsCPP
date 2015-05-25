#include <iostream>
using namespace std;

/**
 *  TODO: Passing 2D arra to a function.
 */
void printSpiral(int** M, int rs, int re, int cols, int cole)
{
	/** Print the top row first */
	for (int ci = cols; ci <= cole; ++ci)
		cout << M[rs][ci] << " ";
}
void printMatrixSpiral(int** M, int R, int C)
{
	int rs = 0, re = R-1, cs = 0, ce = C-1;
	while (rs <= re && cs <= ce)
	{
		printSpiral(M, rs, re, cs, ce);
		++rs;--re;++cs;--ce;
	}
}
int main_printspiral()
{
	int R = 3;
	int C = 6;
	int** M = new int*[R];
	for (int i = 0; i < R; ++i)
		M[i] = new int[6];
	for (int i = 0; i < R; ++i)
	{
		for (int j = 0; j < C; ++j)
			M[i][j] = 0;
	}
	printMatrixSpiral(M, R, C);
	return 0;
}