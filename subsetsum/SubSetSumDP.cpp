#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

/**
 * Recursive solution, S is the set
 * n = array index, can be -1 to indicate no item.
 * SubSet(S, n, T) = SubSet(S, n-1, T) || SubSet(S, n-1, T-a[i])
 *       If there are no items, i.e. n = -1 and T == 0, True
 *       If there are no items, i.e. n == -1 and T == 0, False
 *
 * The array S is 0 based
 * n is the index into the array starting from 0
 * n == -1 implies no more elements in the array or an empty array
 * An empty array is a subset {} and will sum to 0.
 *
 * Time Complexity is 2^n 
 * Space complexity is n (height of the tree)
 */
int subset_sum_recursive(int S[], int n, int T)
{
	/** If there are no more elements and T is 0, this is a solution */
	if (n == -1 && T == 0)
		return 1;
	/** Otherise, if n is -1, then there are no more elements and this is not a solution */
	else if (n == -1)
		return 0;
	/** True if there is a subset of n-1 elements, i.e no S[n] or subset of n-1, T-S[n] */
	return subset_sum_recursive(S, n-1, T) || subset_sum_recursive(S, n-1, T-S[n]);
}

/**
 * Backtracking solution with pruning
 * 1. Assume input is sorted.
 * 2. S = input array
 * 3. n = -1, i.e. start with empty set.
 * 4. T = Sum to find.
 * 5. R = Remaining sum of items left. 
 * 6. len = length of the array
 * 7. C = current weight
 * 8. s = stack to hold the solution nodes.
 *        Doing pass by value as I am printing all the nodes.
 */
void subset_sum_backtracking_pruning(int S[], int len, int n, int C, int T, int R, stack<int, vector<int> > s)
{
	if (n < len && T == C)
	{
		// copy this stack as a vector
		// this is a solution. Print the queue.
		int* end = &s.top()+1;
		int* start = end - s.size();
		vector<int> v (start,end);
		while (s.empty() == false) {
			cout << " " << s.top() << endl;
			s.pop();
		}
		cout << "--------" << endl;
		return ;
	}
	else if (n >= len)
		return ;
	/** Pruning code 
	 * if C + S[n+1] > T return false, i.e. current + next node is > Total, there is no solution.
	 * This covers the case for the n+1 element being included.
	 */
	if ( C + S[n+1] > T )
	{
		return ;
	}
	/** If current weight + remining is less than Total, then there is no chance of matching the target, return false */
	if ( C + R < T )
		return ;
	/** S[n+1] not included in the solution */
	subset_sum_backtracking_pruning(S, len, n+1, C, T, R-S[n+1],s);
	/** Inlcude S[n+1] in the solution. this is why it is pushed in the solution.*/
	s.push(S[n+1]);
	subset_sum_backtracking_pruning(S, len, n+1, C+S[n+1], T, R-S[n+1],s) ;
	s.pop();	   
}
void subset_sum_backtracking_pruning_test()
{
	/** Note sorted input */
	int weights[] = {5,6,10,11,16};
	int len = sizeof(weights)/sizeof(int);
	/** R = remaning weight, initialized to sum of the array */
	int R = 0;
	for (int i = 0; i < len; ++i)
		R += weights[i];
	/** Queue to hold the solution nodes */
	stack<int, vector<int> > q;
	/** C = current sum */
	int C = 0;
	/** W = target weight */
	int W = 21;
	/** Perform operation */
	subset_sum_backtracking_pruning(weights,len,-1,C,W,R,q);
}

int subsetsum_recursive_memoized(int S[], int n, int T, int** M)
{
	if (n == 0 && T == 0)
		return 1;
	if (n == 0 && T != 0)
		return 0;
	if (T < 0)
		return 0;
	if (M[n][T] != -1)
		return M[n][T];
	M[n][T] =  subsetsum_recursive_memoized(S, n-1, T-S[n],M) || subsetsum_recursive_memoized(S, n-1,T,M );
	return M[n][T];
}
void subsetsum_recursive_memoized_test()
{
	int S[] = {0,3, 2, 7, 1};
	int **M = new int*[5];
	for (int i = 0; i < 5; ++i)
		M[i] = new int[7];
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 7; ++j)
			M[i][j] = -1;
	int n = 4;
	int T = 6;
	int result = subsetsum_recursive_memoized(S, n, T, M);
	cout << "Subset sum exists: " << result << endl;
	for (int i = 0; i < 7; ++i)
	{
		delete [] M[i];
	}
	delete [] M;
}
void subsetsum_recursive_test()
{
	int S1[] = {3, 2, 7, 1};
	int result1 = subset_sum_recursive(S1, 3, 6);
	cout << "Subset sum status: " << result1 << endl;
}

void subsetsum_dynamic_programming_test()
{
	int S[] = {0, 3, 2, 7, 1};
	int W = 6;
	int len = sizeof(S)/sizeof(int);
	bool ** M = new bool*[len];
	
	for (int i = 0; i < len; ++i)
		M[i] = new bool[W+1];
	/** Initialize the whole matrix to be false */
	for (int i = 0; i < len; ++i)
		for (int j = 0; j <= W; ++j)
			M[i][j] = false;

	/** If there is no item, its sum is 0, so M[i][0] is T always */
	for (int i = 0; i < len; ++i)
		M[i][0] = true;

	/** Now create the rest of the matrix, it is same as one used in memoized recursion */
	for (int i = 1; i < len; ++i)
	{
		for (int w = 1; w <= W; ++w)
		{
			/** If S[i] > current weight,  as w-S[i] will be less than 0 */
			if (S[i] > w)
				M[i][w] = M[i-1][w];
			else
				M[i][w] = M[i-1][w] || M[i-1][w-S[i]];
		}
	}
	cout << "Subset sum for sum 6 is " << M[len-1][W] << endl;
	for (int i = 0 ; i < len; ++i)
		delete [] M[i];
	delete [] M;
}

void main()
{
	subsetsum_dynamic_programming_test();
	subset_sum_backtracking_pruning_test();
	subsetsum_recursive_test();
	
}