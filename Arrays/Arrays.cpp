// Arrays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>
/**
* Find the mid of the indices.
* if mid is 0 or mid >= mid-1 and mid is n-1 or mid >= mid+1 return the item
* if mid <= mid+1, search in mid+1, hi
* otherwise mid > mid-1, search in lo, mid-1
*/
static int peak1D(int* a, int lo, int hi, int n)
{
	int mid = lo + (hi-lo)/2;
	if ((mid == 0 || a[mid] >= a[mid-1]) && (mid == n-1 || a[mid] >= a[mid+1]))
		return a[mid];
	if (a[mid] < a[mid+1])
		return peak1D(a, mid+1, hi, n);
	return peak1D(a, lo, mid-1, n);
}

static void testPeak1D()
{
	int  a[] = {4,8,5,25,20,18,13,4,5,6,10};
	int length = sizeof(a)/sizeof(a[0]);
	int peak = peak1D(a, 0, length-1, length);
	fprintf(stdout, "%d", peak);
	fflush(stdout);
}

static int testPeak2D()
{
	int m[ ][3] = { {10, 8, 5 },
				{3, 2, 1 },
				{7, 13, 4 },
				{6,8,3}};
	int rows = sizeof(m)/sizeof(m[0]);
	int cols = sizeof(m[0])/sizeof(m[0][0]);
	int* aux = new int[sizeof(m[0])/sizeof(m[0][0])];
	memset(aux,0,sizeof(m[0]));
	for (int col = 0; col < cols; ++col) {
		for (int row = 0; row < rows; ++row) {
			if (m[row][col] > aux[col])
				aux[col] = m[row][col];
		}
	}
	int peak =  peak1D(aux,0,cols-1,cols);
	fprintf(stdout,"%d", peak);
	fflush(stdout);
	return peak;
}
int main()
{
	//testPeak1D();
	testPeak2D();
	return 0;
}

