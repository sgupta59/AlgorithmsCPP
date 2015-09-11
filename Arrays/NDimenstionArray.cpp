#include <iostream>
using namespace std;

void one_dimensioal_allocation()
{
	int* one_dimension = new int[10];
	for (int i = 0; i < 10; ++i)
		one_dimension[i] = 1+i;

	for (int i = 0; i < 10; ++i)
		cout << one_dimension[i] <<  " ";
	cout << endl;
	delete[] one_dimension;
}

/**
 * Non contiguous allocation 
 */
void twoD_DoublePointers()
{
	int ROWS = 3;
	int COLUMNS = 4;
	int** arr = new int*[ROWS];
	for (int i = 0; i < ROWS; ++i)
		arr[i] = new int[COLUMNS];
	for (int i = 0; i < ROWS; ++i)
		for (int j = 0; j < COLUMNS; ++j)
			arr[i][j] = i+j;

	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLUMNS; ++j) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < ROWS; ++i)
		delete[] arr[i];
	delete[] arr;
}

void twoD_singleBlockTest()
{
	int ROWS = 3;
	int COLUMN = 4;
	int* arr = new int[ROWS*COLUMN];
	for (int i = 0; i < ROWS; ++i) 
		for (int j = 0; j < COLUMN; ++j)
			arr[j+i*COLUMN] = i+j;
	
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLUMN; ++j) {
			cout << arr[j+i*COLUMN] << " ";
		}
		cout << endl;
	}
	
	delete arr;
}

void threeD_allocation()
{
	int X = 3;
	int Y = 4; 
	int Z = 4;

	int*** arr = new int**[X];
	for (int i = 0; i < X; ++i)
		arr[i] = new int*[Y];
	for (int i = 0; i < X; ++i)
		for (int j = 0; j < Y; ++j)
			arr[i][j] = new int[Z];
	for (int i = 0; i < X; ++i)
		for (int j = 0; j < Y; ++j)
			for (int k = 0; k < Z; ++k)
				arr[i][j][k] = i+j+k;

	for (int i = 0; i < X; ++i) {
		for (int j = 0; j < Y; ++j) {
			for (int k = 0; k < Z; ++k) {
				cout << arr[i][j][k] << " ";
			}  
			cout << "\t\t";
		}
		cout << endl;
	}
	for (int i =0; i < X; ++i) {
		for (int j = 0; j < Y; ++j) {
			delete [] arr[i][j];
		}
		delete [] arr[i];
	}
	delete [] arr;
}
void main()
{
	threeD_allocation();

	
}