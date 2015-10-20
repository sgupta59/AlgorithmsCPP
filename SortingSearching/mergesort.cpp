#include <iostream>
#include <string>
using namespace std;

void merge(int arr[], int* aux, int lo, int mid, int hi)
{
		for (int k = lo; k <= hi; ++k)
			aux[k] = arr[k];
		int i = lo;
		int j = mid+1;
		for (int k = lo; k <= hi; ++k)
		{
			if (i > mid)     			arr[k] = aux[j++];
			else if (j > hi) 			arr[k] = aux[i++];
			else if (aux[i] < aux[j]) 	arr[k] = aux[i++];
			else 						arr[k] = aux[j++];
		}
}
void mergesort(int arr[], int* aux, int lo, int hi)
{
	if (lo >= hi) return;
	int mid = lo + (hi-lo)/2;
	mergesort(arr, aux, lo, mid);
	mergesort(arr, aux, mid+1, hi);
	merge(arr, aux, lo, mid, hi);
}
void main()
{
	int  arr[] = {1, 50, 25, 33, 2 , 20, 45, 20, 60, 3};
	int* aux = new int[sizeof(arr)/sizeof(int)];

	int hi = sizeof(arr)/sizeof(int)-1;

	mergesort(arr, aux, 0, hi);
	delete [] aux;
}