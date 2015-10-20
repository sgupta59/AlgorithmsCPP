#include <iostream>
#include <string>
using namespace std;
void swap(int A[], int i, int j)
{
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
	return;
}
int partition1(int A[], int lo, int hi)
{
	int pivot = A[lo];
	int p = lo;
	for (int i = lo+1; i <= hi; ++i)
	{
		if (A[i] < pivot) {
			++p;
			swap(A, i, p);
		}
	}
	swap(A, lo, p);
	return p;
}
/**
	partition the subarray a[lo..hi] so that a[lo..j-1] <= a[j] <= a[j+1..hi]
 */
int partition(int A[], int lo, int hi)
{
	int p = A[lo];
	int i = lo;
	int j = hi+1;
	while (true) {
		while (A[++i] < p)
			if (i == hi) break;
		while (A[--j] > p)
			if (j == lo) break;
		if (i >= j) break;
		int tmp = A[i];
		A[i] = A[j];
		A[j] = tmp;
	}
	int tmp = A[j];
	A[j] = p;
	A[lo]  = tmp;
	/** lo ... j-1 <= p <= j+1 ... hi */
	return j;
}
void qsort(int* A, int lo, int hi)
{
	if (lo == hi)
		return;
	int pivot = partition(A, lo, hi);
	qsort(A, lo, pivot);
	qsort(A, pivot+1,hi);
}

/**
 * Selection of the i'th item in an array A
 * Here i is absolute, i.e. even if lo = hi = 5, and i = 5, 
 * the right result is returned, but in an array of A[0], i is 5 
 * so the result is just strange 
 */
int select(int A[], int lo, int hi, int i)
{
	int p = partition(A, lo, hi);
	if (p > i) return select(A, lo, p-1, i);
	if (p < i) return select(A, p+1, hi, i);
	return A[p];
}
/**
 * Selection based on 1 based indexing.
 * The i'th item is based on 1 based indexing.
 * The pivot index i.e. p gives an array [lo,p] which are <= A[p].
 * There are p-lo+1 items in this array.
 * if i > p-lo+1, then the position of i in the array [p+1, hi] will be:
   i - {# of items in the less array, i.e. p-lo+1 }
 */
int quick_select(int A[], int lo, int hi, int i)
{
	if (lo == hi)
		return A[lo];
	/** Get the partition index, now the array is A[lo...p-1] <= A[p] <= A[p+1...hi] */
	int p  = partition(A, lo, hi);
	/** Get number of elekents in the array A[lo...k], i.e. number of elements <= A[k]. */
	int k = (p-lo+1);
	if (i == k) 
		return A[p];
	/** if i < k, then go [lo, p-1] */
	if (i < k) return quick_select(A,lo,p-1,i);
	/** Otherwise, look for the i-k'th element in the array indexed A[p+1, hi] */
	return quick_select(A,p+1,hi,i-k);
}

/**
 * A 3 way quick sort will divide an array into following parts
 * lo......lt.......i........gt.......hi
 * [lo,lt-1] --> less than pivot
 * [lt, i-1] --> == pivot
 * [i, gt]   --> Unknown
 * [gt+1, hi] --> greater
 */
void qsort_3way(int a[], int lo, int hi)
{
	int pivot = a[lo];
	int i = lo;
	int gt = hi;
	int lt = lo;
	while (i <= gt) {
		if (a[i] < pivot) {
			swap(a,lt,i);
			++i;
			++lt;
		} else if (a[i] > pivot) {
			swap(a, i, gt);
			--gt;
		} else {
			++i;
		}
	}
	qsort_3way(a, lo, lt-1);
	qsort_3way(a, gt+1, hi);
}
void main()
{
	int test[] = { 7, -13, 1, 3, 10, 5, 2, 4 };
	// sorted--> { -13, 1, 2, 3, 4, 5, 7, 10 }
    int N = sizeof(test)/sizeof(int);
	int *test1 = (int*)malloc(sizeof(int)*N);
	memcpy(test1,test,sizeof(int)*N);
	for (int i = 0; i < N; ++i)
	{
		memcpy(test1, test, N*sizeof(int));
		cout << i << "'th selection: " << select(test1,0,N-1,i) << endl;
	}
			
	memcpy(test1, test, N*sizeof(int));
	cout << 6 << "'th selection: " << quick_select(test1,0,N-1,6) << endl;
	for (int i = 0; i < N; ++i)
	{
		memcpy(test1, test, N*sizeof(int));
		cout << i+1 << "'th selection: " << quick_select(test1,0,N-1,i+1) << endl;
	}
	qsort(test,0,N-1);
	cout << "end" << endl;
}