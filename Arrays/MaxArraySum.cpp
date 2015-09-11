#include <iostream>
using namespace std;
/** http://www.cse.ust.hk/faculty/golin/COMP271Sp03/Notes/L02.pdf */

/**
 * This is a brute for solution where each interval between i and [i,N] is summed and compared.
 */
int maxSum_cubic(int* a, int len)
{
	int max = 0;
	// for each i
	for (int i = 0; i < len; ++i) {
		// for j = i to N
		for (int j = i; j < len; ++j) {
			int sum = 0;
			// sum k = i to j
			for (int k = i; k <= j; ++k) {
				sum += a[k];
			}
			// if sum is > max save it.
			if (sum > max)
				max = sum;
		}
	}
	return max;
}
/**
 * Quadratic solution, uses previous calculations to create new sum
 * sum = a(0) + a(1) ... a(i-1)
 * new sum = sum + a(i)
 */
int maxSum_quadratic(int* a, int len)
{
	int max = 0;
	for (int i = 0; i < len; ++i) {
		int sum = 0;
		for (int j = i; j < len; ++j) {
			sum = sum + a[j];
			if (sum > max) max = sum;
		}
	}
	return max;
}
/**
 * nLogn solution.
 * Uses divide and conquer
 * max sum is either the left part or right part or one at the boundary
 * e.g.
 * 0....M, M+1, .... N
 * max sum = max (0...M) or max (m+1...N) or max(...M, M+1, ...) i.e. the boundary
 */
int maxSum_divideAndConquer(int* a, int lo, int hi)
{
	if (lo==hi)
		return a[lo];
	int mid = lo + (hi-lo)/2;
	int left = maxSum_divideAndConquer(a, lo, mid);
	int right = maxSum_divideAndConquer(a, mid+1, hi);
	int sum_l = 0; int sum = 0;
	for (int i = mid; i >= lo; --i) {
		sum = sum + a[i];
		if (sum > sum_l)
			sum_l = sum;
	}
	int sum_r = 0; sum = 0;
	for (int i = mid+1; i <= hi; ++i)
	{
		sum = sum + a[i];
		if (sum > sum_r)
			sum_r = sum;
	}
	 sum = sum_l + sum_r;
	if (sum > left)
		return sum > right ? sum : right;
	return left > right ? left : right;
}
/**
 * Linear solution.
 * sum(i,j) = sum(j) - sum(i-1),where sum(j) is cummulative sum [0,j] and sum(i-1) is sum[0,i-1]
 * now max sum(i,j) is sum(j) - sum(i-1) where sum(i-1) is the minimum sum for a given i.
 */
int maxSum_dynamic(int* a, int len)
{
	// max is the max sum so far, i.e sum(i,j) range
	int max = a[0];
	// min is the minimum sum up to an index i.
	int min = a[0];
	// sum is the current sum
	int sum = a[0];
	// min is either negative or 0 to start.
	if (min >= 0)
		min = 0;
	for (int i = 1; i < len; ++i)
	{
		// get cummulative sum up to i.
		sum = sum+a[i];
		// subtract the minimum from current sum. if this is greater than max, then this is
		// the new range of (i,j) where min is some sum up to i-1.
		if (sum - min > max)
			max = sum-min;
		// if this sum is less than the minimum, then this is the new minimu,
		if (sum < min)
			min = sum ;
	}
	return max;
}
void main()
{
	int arr[] = {-3, 2, 1, -4, 5, 2, -1, 3, -1};
	cout << "Max Sum: " << maxSum_cubic(arr, sizeof(arr)/sizeof(int)) << endl;
	cout << "Max Sum: " << maxSum_quadratic(arr, sizeof(arr)/sizeof(int)) << endl;
	cout << "Max Sum: " << maxSum_divideAndConquer(arr,0, sizeof(arr)/sizeof(int)-1) << endl;
	cout << "Max Sum: " << maxSum_dynamic(arr, sizeof(arr)/sizeof(int)) << endl;
}